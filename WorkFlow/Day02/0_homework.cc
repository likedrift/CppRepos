#include <iostream>
#include <string>
#include <signal.h>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

static string key = "x1";

static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum){
    cout << "signum = " << signum << "\n";
    gWaitGroup.done();
}


void redisCallback(WFRedisTask *redisTask){
    protocol::RedisRequest *req = redisTask->get_req();
    protocol::RedisResponse *resp = redisTask->get_resp();
    protocol::RedisValue value;

    int state = redisTask->get_state();
    int error = redisTask->get_error();

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

    if(state == WFT_STATE_SUCCESS){
        cout << "SUCCESS\n";
    }else{
        cout << "FAILED\n";
        return;
    }

    if(value.is_string() && value.string_value()[0] == 'x'){
        cout << "value is a string, value = " << value.string_value() << "\n";
        key = value.string_value();
    }else{
        cout << "finally get the value = " << value.string_value() << "\n";
        exit(0);
    }
}

int main(void){
    signal(SIGINT, handler);
    // WFRedisTask *redisTask =
    //     WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
    // protocol::RedisRequest *req = redisTask->get_req();
    // req->set_request("GET", {key});
    // SeriesWork *series = Workflow::create_series_work(redisTask, nullptr);
    // int cnt = 5;
    while(true){
        sleep(1);
        cout << "key = " << key << "\n";
        WFRedisTask *redisTask =
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
        protocol::RedisRequest *req = redisTask->get_req();
        req->set_request("GET", {key});
        // SeriesWork *series = Workflow::create_series_work(redisTask, nullptr);
        redisTask->start();
    }

    gWaitGroup.wait();
    return 0;
}