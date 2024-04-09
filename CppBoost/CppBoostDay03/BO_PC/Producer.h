#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "Thread.h"

class TaskQueue;

class Producer : public Thread{
public:
    Producer(TaskQueue &taskQue);
    void run() override;

private:
    TaskQueue &_taskQue;
};

#endif