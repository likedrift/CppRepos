#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "Thread.h"
class TaskQueue;

class Producer{

public:
    // Producer(TaskQueue &taskQue);
    Producer();
    ~Producer();
    void run(TaskQueue &taskQue);
// private:
//     TaskQueue &_taskQue;
};

#endif