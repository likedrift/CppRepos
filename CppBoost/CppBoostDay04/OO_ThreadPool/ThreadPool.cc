#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQueue(_queSize)
,_isExit(false)
{
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool(){

}

void ThreadPool::start(){
    
    // 创建出所有的工作线程
    for(size_t idx = 0; idx != _threadNum; ++idx){
        _threads.push_back(unique_ptr<Thread>(new WorkThread(*this)));
    }

    // 将所有的工作线程运行起来
    for(auto &th : _threads){
        th->start();
    }
}

void ThreadPool::stop(){
    // 任务如果未执行完，就不能让子线程退出
    while(!_taskQueue.empty()){
        sleep(1);
    }
    _isExit = true;

    // 唤醒所有睡眠的工作线程
    _taskQueue.wakeup();

    // 停止所有工作线程
    for(auto &th : _threads){
        th->stop();
    }
}

void ThreadPool::addTask(Task *pTask){
    if(pTask){
        _taskQueue.push(pTask);
    }
}

Task *ThreadPool::getTask(){
    return _taskQueue.pop();
}

void ThreadPool::doTask(){
    while(!_isExit){
        Task *ptask = getTask();
        if(ptask){
            ptask->process();
        }else{
            cout << "ptask == nullptr" << endl;
        }
    }
}