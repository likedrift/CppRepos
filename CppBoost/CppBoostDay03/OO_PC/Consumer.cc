#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

Consumer::Consumer()
{

}
Consumer::~Consumer(){
    
}

void Consumer::run(TaskQueue &taskQue){
    int count = 5;
    while(count--){
        int val = taskQue.pop();
        cout << "Consumer consumed : " << val << endl;
        sleep(1);
    }
}
