#include <iostream>
#include <nlohmann/json.hpp>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFHttpServer.h>
#include <signal.h>
#include <string>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;
using json = nlohmann::json;
using std::string;

static WFFacilities::WaitGroup gWaitGroup(1);

struct SeriesContext{
    // string chkidx;
    protocol::HttpResponse * resp;
};

void handler(int signum){
    cout << "signum = " << signum << "\n";
    gWaitGroup.done();
}

void setRedisTask(WFHttpTask *serverTask, string uploadID, string key, string value){
    WFRedisTask *redisTask = 
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, nullptr);
    redisTask->get_req()->set_request("HSET",{uploadID, key, value});
    series_of(serverTask)->push_back(redisTask);
}

void redisCallback(WFRedisTask *redisTask){
    protocol::RedisResponse * resp = redisTask->get_resp();
    protocol::RedisValue value;
    resp->get_result(value);

    size_t size = value.arr_size();
    cout << "size = " << size << endl;

    string chunkCount;
    size_t spliceCount;

    // 提取共享的数据
    SeriesContext *context = (SeriesContext *)series_of(redisTask)->get_context();
    
    for(size_t i = 0; i < size; ++i){
        if(value.arr_at(i).string_value() == "chunkCount"){
            chunkCount = value.arr_at(i+1).string_value();
        }
        if(value.arr_at(i).string_value().find("chkidx_",0)){
            ++spliceCount;
        }
    }
    if(spliceCount == atoi(chunkCount.c_str())){
        context->resp->append_output_body("OK");
    }else{
        context->resp->append_output_body("NO");
    }
    // cout << value.arr_at(0).string_value() << endl;
    // cout << value.arr_at(1).string_value() << endl;
}

void process(WFHttpTask *serverTask){
    protocol::HttpRequest * req = serverTask->get_req();
    protocol::HttpResponse * resp = serverTask->get_resp();
    // 获取方法
    string method = req->get_method();
    // 获取路径
    // 这里get_request_uri获取到的是域名或ip后面的内容
    // 比如http://192.168.174.128:1234/test?user=liao&password=123
    string path = req->get_request_uri();
    // 获取的就是uri = /test?user=liao&password=123
    // cout << "path = " << path << "\n"; 

    string subPath = path.substr(0,path.find("?"));

    // cout << subPath << endl;
    // cout << id << endl;
    // cout << idx << endl;

    // if-else if-else 做路由匹配
    if(method == "POST" && path == "/file/mupload/init"){
        // 解析json
        const void * body;
        size_t size;
        req->get_parsed_body(&body,&size);
        string bodyValue = string((char *)body, size);

        json jsonValue = json::parse(bodyValue);
        // 拿到filename、hash、size
        auto getFilename = jsonValue["filename"].get<string>();
        auto getHash = jsonValue["hash"].get<string>();
        auto getSize = jsonValue["size"].get<string>();

        cout << "filename = " << getFilename << endl;
        cout << "hash = " << getHash << endl;
        cout << "size = " << getSize << endl;
        
        // 生成分片信息
        srand(time(NULL));
        string uploadID = std::to_string(rand());

        // 算分片
        int totalSize = atoi(getSize.c_str());
        int chunkSize = 1024;
        int chunkCount = ceil(totalSize / (1024 * 1.0));
        string name = "user";
        string hash = "abc123";

        // Redis任务
        setRedisTask(serverTask,uploadID,"name",name);
        setRedisTask(serverTask,uploadID,"hash",hash);
        setRedisTask(serverTask,uploadID,"size",getSize);
        setRedisTask(serverTask,uploadID,"chunkCount",std::to_string(chunkCount));
        setRedisTask(serverTask,uploadID,"chunkSize",std::to_string(chunkSize));

        // 回复给客户端
        resp->add_header_pair("name",name);
        resp->add_header_pair("hash",hash);
        resp->add_header_pair("size",getSize);
        resp->add_header_pair("chunkCount",std::to_string(chunkCount));
        resp->add_header_pair("chunkSize",std::to_string(chunkSize));
    }else if(method == "POST" && subPath == "/file/mupload/uppart"){
        // 提取uploadID和idx
        cout << "1\n" << endl;
        string uploadIdKV = path.substr(0, path.find("&"));
        string uploadID = uploadIdKV.substr(uploadIdKV.find("=") + 1);
        string idxKV = path.substr(path.find("&") + 1);
        string idx = idxKV.substr(idxKV.find("=") + 1);

        // 保存在文件系统中
        protocol::HttpRequest * req = serverTask->get_req();
        protocol::HttpResponse * resp = serverTask->get_resp();

        string method = req->get_method();
        cout << "2\n";
        const void *body;
        size_t size;
        req->get_parsed_body(&body, &size);
        string bodyStr = static_cast<const char *>(body);

        mkdir(uploadID.c_str(), 0777);
        string path = uploadID;
        path += "/";
        path += idx;
        cout << "path = " << path << endl;
        int fd = open(path.c_str(), O_RDWR | O_CREAT, 0666);
        write(fd, bodyStr.c_str(), size);

        // 写入Redis
        string key = "chkidx_";
        key += idx;
        setRedisTask(serverTask, uploadID, key, idx);
    }else if(method == "POST" && subPath == "/file/mupload/complete"){
        string uploadIdKV = path.substr(0, path.find("&"));
        string uploadID = uploadIdKV.substr(uploadIdKV.find("=") + 1);
        cout << "uploadID = " << uploadID << endl;

        // 设置共享的数据
        SeriesContext * context = new SeriesContext;
        context->resp = serverTask->get_resp();
        series_of(serverTask)->set_context(context);

        // HGETALL
        WFRedisTask * redisTask = 
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
        redisTask->get_req()->set_request("HGETALL",{uploadID});
        series_of(serverTask)->push_back(redisTask);
    }
}

int main(void){
    signal(SIGINT, handler);
    // auto config_json = json::parse(R"({"happy": true, "pi": 3.141})");  //构建json对象
    // cout << config_json << endl;   //输出json对象值
    WFHttpServer server(process);
    server.start(1234);
    gWaitGroup.wait();
    server.stop();
    return 0;
}