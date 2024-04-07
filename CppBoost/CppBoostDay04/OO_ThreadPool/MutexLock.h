#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>
#include "NonCopyable.h"

class MutexLock : public NonCopyable{
public:
    // 构造函数中初始化锁
    MutexLock();
    // 析构函数中摧毁锁
    ~MutexLock();
    // 上锁
    void lock();
    // 解锁
    void unlock();
    // 尝试上锁
    void trylock();
    // 得到锁
    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard{
public:
    MutexLockGuard(MutexLock &mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard(){
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};

#endif