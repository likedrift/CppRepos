#include "Producer.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using std::cout;
using std::endl;

Producer::Producer(TaskQueue &taskQue)
:_taskQue(taskQue)
{

}

void Producer::run(){
    srand(time(NULL));
    int count = 5;
    while(count--){
        int val = rand() % 50 + 1;
        _taskQue.push(val);
        cout << "Producer produced : " << val << endl;
        sleep(1);
    }
}