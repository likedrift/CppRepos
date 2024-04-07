#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include <memory>
#include "TaskQueue.h"

using std::vector;
using std::unique_ptr;

class Thread;
class Task;

class ThreadPool{
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Task *pTask);

private:
    Task *getTask();
    void doTask();

private:
    size_t _threadNum; // 线程数量
    size_t _queSize; // 任务队列大小
    vector<unique_ptr<Thread>> _threads; // 存放工作线程 基类指针的容器
    TaskQueue _taskQueue;
    bool _isExit;
};


#endif