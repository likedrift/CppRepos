#include "MutexLock.h"
#include <stdio.h>


MutexLock::MutexLock(){
    // 构造函数对mutex进行初始化
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret){
        perror("pthread_mutex_init");
        return;
    }
}

MutexLock::~MutexLock(){
    // 析构函数销毁mutex
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret){
        perror("pthread_mutex_destroy");
        return;
    }
}

void MutexLock::lock(){
    // 上锁
    int ret = pthread_mutex_lock(&_mutex);
    if(ret){
        perror("pthread_mutex_lock");
        return;
    }
}

void MutexLock::unlock(){
    // 解锁
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret){
        perror("pthread_mutex_unlock");
        return;
    }
}

void MutexLock::trylock(){
    // 尝试上锁
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret){
        perror("pthread_mutex_trylock");
        return;
    }
}

pthread_mutex_t * MutexLock::getMutexLockPtr(){
    return &_mutex;
}
