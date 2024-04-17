#include <iostream>
#include <vector>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <signal.h>

using std::cout;
using std::string;
using std::vector;

struct SeriesContext{
    string url;
    size_t size;
};

static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum){
    cout << "signum = " << signum << "\n";
    gWaitGroup.done();
}

void httpCallback(WFHttpTask *httpTask){
    cout << "http callback\n";
    protocol::HttpResponse *resp = httpTask->get_resp();
    cout << resp->get_http_version() << " "
         << resp->get_status_code() << " "
         << resp->get_reason_phrase() << "\n";
    const void *body;
    size_t size;
    resp->get_parsed_body(&body, &size);
    cout << "size = " << size << "\n";
    // 通过series_of(httpTask)获取与httpTask关联的系列任务对象
    // 然后调用其get_context()方法获取系列任务对象的上下文对象

    SeriesContext * context = (SeriesContext*)series_of(httpTask)->get_context();
    context->size = size;
}

void parallelCallback(const ParallelWork * parallel){
    cout << "parallel callback\n";
    for(size_t i = 0; i < parallel->size(); ++i){
        SeriesContext * context = (SeriesContext *)parallel->series_at(i)->get_context();
        cout << "url = " << context->url << ", size = " << context->size << "\n";
        delete(context);
    }
}


int main(){
    signal(SIGINT, handler);
    vector<string> vec{
        "http://www.jd.com",
        "http://www.taobao.com",
        "http://www.bilibili.com"
    };

    ParallelWork * parallel = Workflow::create_parallel_work(parallelCallback);
    for(int i = 0; i < vec.size(); ++i){
        WFHttpTask * httpTask = 
            WFTaskFactory::create_http_task(vec[i], 10, 0, httpCallback);
        SeriesWork * series = Workflow::create_series_work(httpTask, nullptr);
        SeriesContext * context = new SeriesContext;
        series->set_context(context);
        context->url = vec[i];
        parallel->add_series(series);
    }
    parallel->start();
    gWaitGroup.wait();
}