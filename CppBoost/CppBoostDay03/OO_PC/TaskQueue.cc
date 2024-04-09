#include "TaskQueue.h"
#include "Condition.h"
TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_que()
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
{

}

TaskQueue::~TaskQueue(){

}

void TaskQueue::push(const int &value){
    // 上锁
    MutexLockGuard autoLock(_mutex);

    // 1.检查queue是否已满
    while(full()){
        // 队列满了就让生产者等待
        _notFull.wait();
    }

    // 2.队列不满就生产者就生产并放入商品
    _que.push(value);
    // 3.唤醒消费者
    _notEmpty.notify();
}

int TaskQueue::pop(){
    // RAII
    MutexLockGuard autoLock(_mutex);

    // 1.检查queue是否为空
    while(empty()){
        _notEmpty.wait();
    }

    // 2.队列不空，消费商品
    int deValue = _que.front();
    _que.pop();

    // 3.唤醒生产者
    _notFull.notify();
    
    return deValue;
}

bool TaskQueue::full(){
    return _queSize == _que.size();
}

bool TaskQueue::empty(){
    return _que.size() == 0;
}