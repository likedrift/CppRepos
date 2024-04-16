#include <iostream>
#include <signal.h>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum){
    cout << "signum = " << signum << endl;
    gWaitGroup.done();
}

void redisCallback(WFRedisTask *redisTask){
    sleep(1);
    protocol::RedisRequest *req = redisTask->get_req();
    protocol::RedisResponse *resp = redisTask->get_resp();
    protocol::RedisValue value;
    int state = redisTask->get_state();
    int error = redisTask->get_error(); // error只能处理网络连接和系统错误
    switch (state){
    case WFT_STATE_SYS_ERROR:
        cout << "system error:" << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        cout << "dns error: " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(value); // 将redis的结果已经存在value中了
        if (value.is_error())
        {
            cout << "redis error\n";
            state = WFT_STATE_TASK_ERROR; // 任务层面的错误
        }
        break;
    }
    if (state == WFT_STATE_SUCCESS){
        cout << "SUCCESS\n";
    }else{
        cout << "FAILED\n";
        return;
    }

    if(value.is_string()){
        cout << "bodyValue = " << value.string_value() << "\n";
    }
}

void httpCallback(WFHttpTask *httpTask){
    protocol::HttpRequest *req = httpTask->get_req();
    protocol::HttpResponse *resp = httpTask->get_resp();
    int state = httpTask->get_state();
    int error = httpTask->get_error();
    switch(state){
    case WFT_STATE_SYS_ERROR:
        cout << "system error:" << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        cout << "dns error: " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SUCCESS:
        break;
    }
    if(state == WFT_STATE_SUCCESS){
        cout << "SUCCESS\n"; 
    }
    else{
        cout << "FAILED\n";
        return;
    }

    const void *body;
    size_t size;
    resp->get_parsed_body(&body,&size);

    string bodyValue = string((char *)body, size);
    cout << bodyValue << endl;
    // 新任务 redis -- set
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
    protocol::RedisRequest *req2 = redisTask->get_req();
    req2->set_request("SET",{"www.taobao.com",bodyValue});
    sleep(1);
    redisTask->start();
}

int main(void){
    signal(SIGINT, handler);
    WFHttpTask *httpTask = 
        WFTaskFactory::create_http_task("http://www.taobao.com", 10, 0, httpCallback);
    protocol::HttpRequest *req = httpTask->get_req();
    httpTask->start();
    sleep(1);
    gWaitGroup.wait();
    return 0;
}