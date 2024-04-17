#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <signal.h>
#include <unistd.h>

using std::cout;
using std::endl;
static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum){
    cout << "signum = " << signum << "\n";
    gWaitGroup.done();
}

class Homework{
public:
    void init_query(){
        WFRedisTask * redisTask =
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0,
                        std::bind(&Homework::on_redis_return, this, std::placeholders::_1));
        redisTask->get_req()->set_request("GET",{"x1"});
        redisTask->start();
    }

    void on_redis_return(WFRedisTask * redisTask){
        protocol::RedisResponse *resp = redisTask->get_resp();
        protocol::RedisValue value;
        resp->get_result(value);
        if(value.is_ok() && value.string_value() == "100"){
            cout << "current value is " << value.string_value() << "\n";
            cout << "finished\n";
            return;
        }else{
            cout << "current value is " << value.string_value() << "\n";
            sleep(1);
            WFRedisTask * nextRedisTask = 
                WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0,
                    std::bind(&Homework::on_redis_return, this, std::placeholders::_1));
            nextRedisTask->get_req()->set_request("GET", {value.string_value()});
            series_of(redisTask)->push_back(nextRedisTask);
        }
    }
};

int main(void){
    signal(SIGINT, handler);
    Homework homework;
    homework.init_query();
    gWaitGroup.wait();
    return 0;
}