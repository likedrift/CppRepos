#include <iostream>
#include "Thread.h"
#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <memory>


using std::cout;
using std::endl;
using std::unique_ptr;

void test01(){
    TaskQueue tq(10);
    unique_ptr<Thread> producer(new Producer(tq));
    unique_ptr<Thread> consumer(new Consumer(tq));

    producer->start();
    consumer->start();

    producer->stop();
    consumer->stop();
}

int main(void){
    test01();
    return 0;
}