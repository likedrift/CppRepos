#include <iostream>
#include "Thread.h"
#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <memory>


using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;
using std::ref;

void test01(){
    TaskQueue tq(10);
    Producer pro;
    Consumer con;

    unique_ptr<Thread> producer(new Thread(bind(&Producer::run,&pro,ref(tq))));
    unique_ptr<Thread> consumer(new Thread(bind(&Consumer::run,&con,ref(tq))));

    producer->start();
    consumer->start();

    producer->stop();
    consumer->stop();
}

int main(void){
    test01();
    return 0;
}