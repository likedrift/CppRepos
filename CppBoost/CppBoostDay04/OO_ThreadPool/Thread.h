#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include "NonCopyable.h"
class Thread : NonCopyable{
public:
    Thread();
    virtual ~Thread();

    void start();
    void stop();
private:
    static void *threadFunc(void *arg);
    virtual void run() = 0;

private:
    pthread_t _tid;
    bool _isRunning;
};

#endif