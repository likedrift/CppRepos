#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>
#include "MutexLock.h"

class Condition{
public:
    Condition(MutexLock &mutex);
    ~Condition();
    // pthread_cond_wait
    void wait();
    // pthread_cond_signal
    void notify();
    // pthread_cond_broadcast
    void notifyAll();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};

#endif