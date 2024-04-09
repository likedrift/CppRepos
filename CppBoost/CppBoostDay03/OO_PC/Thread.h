#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;

class Thread{
public:
    using ThreadCallBack = function<void()>;
    Thread(ThreadCallBack &&cb);
    ~Thread();
    // 启动线程
    void start();
    // 停止线程
    void stop();

private:
    // 线程入口函数
    static void *threadFunc(void *arg);
    // 线程需要执行的任务
    void run();

private:
    pthread_t _tid;
    // 判断线程是否在运行状态
    // 给stop()函数使用
    bool _isRunning;
    ThreadCallBack _cb;
};


#endif

