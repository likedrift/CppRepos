#include <iostream>
#include <vector>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <signal.h>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::bind;
using std::cerr;

struct SeriesContext{
    string url;
    size_t size;
};

static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum){
    cout << "sigunm = " << signum << endl;
    gWaitGroup.done();
}

class Test{
public:
    void childSeriesCallback(const SeriesWork * series){
        cout << "child series callback\n";
    }

    void bigSeriesCallback(const SeriesWork * series){
        cout << "big series callback\n";
    }

    void parallelCallback(const ParallelWork * parallel){
        cout << "parallel callback\n";
        for(size_t i = 0; i < parallel->size(); ++i){
            SeriesContext * context = (SeriesContext *)parallel->series_at(i)->get_context();
            cout << "url = " << context->url << ", size = " << context->size;
            delete(context);
        }
        series_of(parallel)->set_callback(bind(&Test::bigSeriesCallback, this, std::placeholders::_1));
    }

    void httpCallback(WFHttpTask * httpTask){
        cout << "http callback\n";
        protocol::HttpResponse * resp = httpTask->get_resp();
        cerr << resp->get_http_version() << " "
             << resp->get_status_code() << " "
             << resp->get_reason_phrase() << "\n";

        const void * body;
        size_t size;
        resp->get_parsed_body(&body, &size);
        cout << "size = " << size << "\n";

        SeriesContext * context = (SeriesContext *)series_of(httpTask)->get_context();
        context->size = size;
    }

    void init_task(){
        vector<string> vec{
            "http://www.jd.com",
            "http://www.bilibili.com",
            "http://www.taobao.com"
        };
        ParallelWork * parallel = Workflow::create_parallel_work(bind(&Test::parallelCallback, this, std::placeholders::_1));
        for(size_t i = 0; i < vec.size(); ++i){
            // 创建http任务
            WFHttpTask * httpTask = 
                WFTaskFactory::create_http_task(vec[i], 10, 0, bind(&Test::httpCallback, this, std::placeholders::_1));
            // 创建序列
            SeriesWork * series = Workflow::create_series_work(httpTask,nullptr);
            series->set_callback(bind(&Test::childSeriesCallback, this, std::placeholders::_1));
            // 申请context
            SeriesContext * context = new SeriesContext;
            series->set_context(context);
            context->url = vec[i];
            // 该序列内有一个任务，再放到大的并行任务序列内
            parallel->add_series(series);
        }
        parallel->start();
    }
};

int main(){
    signal(SIGINT, handler);
    Test test;
    test.init_task();
    gWaitGroup.wait();
}