#include "WorkThread.h"
#include "ThreadPool.h"

WorkThread::WorkThread(ThreadPool &pool)
:_pool(pool)
{

}

WorkThread::~WorkThread(){

}

void WorkThread::run(){
    // 工作线程的run方法执行的
    // 就是线程池交给工作线程做的任务doTask
    _pool.doTask();
}