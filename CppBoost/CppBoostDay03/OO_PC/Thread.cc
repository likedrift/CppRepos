#include "Thread.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Thread::Thread(ThreadCallBack &&cb)
:_tid(0)
,_isRunning(false)
,_cb(std::move(cb)) // 注册
{

}

Thread::~Thread(){

}

void Thread::start(){
    int ret = pthread_create(&_tid,nullptr,threadFunc,this);
    if(ret){
        perror("pthread_create");
        return;
    }
    // 开始执行，将isRunning标志位设置为true
    _isRunning = true;
}


void Thread::stop(){
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
    // arg就是传进来的this指针
    Thread *pth = static_cast<Thread *>(arg);
    if(pth){
        pth->_cb();// 回调
    }else{
        cout << "pth == nullptr" << endl;
    }

    pthread_exit(nullptr);
}