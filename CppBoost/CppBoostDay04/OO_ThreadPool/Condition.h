#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>
#include "MutexLock.h"
#include "NonCopyable.h"
class Condition : public NonCopyable{
public:
    Condition(MutexLock &mutex);
    ~Condition();
    // 等待唤醒
    void wait();
    // 单播唤醒
    void notify();
    // 广播唤醒
    void notifyAll();

private:
    MutexLock & _mutex;
    pthread_cond_t _cond;
};

#endif