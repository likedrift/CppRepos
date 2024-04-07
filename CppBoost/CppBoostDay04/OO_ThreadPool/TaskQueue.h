#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include "MutexLock.h"
#include "Condition.h"
using std::queue;

class Task;

using ElemType = Task *;
class TaskQueue{

public:
    // 除了queSize用传入的参数，其他的数据成员都使用
    // 默认初始化
    TaskQueue(size_t queSize);
    ~TaskQueue();
    void push(ElemType ptask);
    ElemType pop();
    bool full();
    bool empty();
    void wakeup();
private:
    // 任务队列大小
    size_t _queSize;
    // 实际放任务的队列
    queue<ElemType> _que;
    // 互斥锁
    MutexLock _mutex;
    // 非满条件变量-生产者
    Condition _notFull;
    // 非空条件变量-消费者
    Condition _notEmpty;
    // 为了唤醒所有工作线程的时候，可以让while退出
    bool _flag;
};

#endif