#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_que()
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

void TaskQueue::push(ElemType ptask){
    // 先上锁
    MutexLockGuard autoLock(_mutex);
    
    // 如果满就等待
    while(full()){
        _notFull.wait();
    }

    // 不满则push
    _que.push(ptask);

    // 唤醒消费者
    _notEmpty.notify();
}

ElemType TaskQueue::pop(){
    MutexLockGuard autoLock(_mutex);

    while(empty() && _flag){
        _notEmpty.wait();
    }

    if(_flag){
        ElemType tmp = _que.front();
        _que.pop();
        _notFull.notify();
        return tmp;
    }else{
        return nullptr;
    }
}

// 唤醒所有在等待_notEmpty条件变量上的线程
void TaskQueue::wakeup(){
    _flag = false;
    _notEmpty.notifyAll();
}


// 判满
bool TaskQueue::full(){
    return _queSize == _que.size();
}

// 判空
bool TaskQueue::empty(){
    return _que.size() == 0;
}