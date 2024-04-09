#include "Producer.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using std::cout;
using std::endl;

Producer::Producer()
{
}

Producer::~Producer()
{
}

void Producer::run(TaskQueue &taskQue){
    srand(time(NULL));
    int count = 5;
    while(count--){
        int val = rand() % 50 + 1;
        taskQue.push(val);
        cout << "Producer produced : " << val << endl;
        sleep(1);
    }
}