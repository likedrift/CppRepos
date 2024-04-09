#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <iostream>
#include <queue>
#include "MutexLock.h"
#include "Condition.h"
using std::queue;

class TaskQueue{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    void push(const int &value);
    int pop();
    bool full();
    bool empty();

private:
    // 最大容量
    size_t _queSize;
    // FIFO
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

#endif