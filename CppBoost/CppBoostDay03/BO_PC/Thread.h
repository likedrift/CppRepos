#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread{
public:
    Thread();
    virtual ~Thread();
    // 启动线程
    void start();
    // 停止线程
    void stop();

private:
    // 线程入口函数
    static void *threadFunc(void *arg);
    // 线程需要执行的任务
    virtual void run() = 0;

private:
    pthread_t _tid;
    // 判断线程是否在运行状态
    // 给stop()函数使用
    bool _isRunning;
};


#endif

