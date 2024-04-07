#include "Thread.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

Thread::Thread()
:_tid(0)
,_isRunning(false)
{

}

Thread::~Thread(){

}

// 线程启动
void Thread::start(){
    int ret = pthread_create(&_tid,nullptr,threadFunc,this);
    if(ret){
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

// 线程终止
void Thread::stop(){
    // 标志位为true才去join
    if(_isRunning){
        int ret = pthread_join(_tid,nullptr);
        if(ret){
            perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}

void *Thread::threadFunc(void *arg){
    Thread *pth = static_cast<Thread *>(arg);
    if(pth){
        pth->run(); // 走的是doTask
    }else{
        cout << "pth == nullptr" << endl;
    }

    pthread_exit(nullptr);
}