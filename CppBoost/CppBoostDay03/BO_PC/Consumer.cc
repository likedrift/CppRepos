#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

Consumer::Consumer(TaskQueue &taskQue)
:_taskQue(taskQue)
{

}
Consumer::~Consumer(){
    
}

void Consumer::run(){
    int count = 5;
    while(count--){
        int val = _taskQue.pop();
        cout << "Consumer consumed : " << val << endl;
        sleep(1);
    }
}
