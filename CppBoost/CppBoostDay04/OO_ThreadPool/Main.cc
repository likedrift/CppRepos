#include "Task.h"
#include "ThreadPool.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <memory>
#include <unistd.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask : public Task{
public:
    void process() override{
        srand(clock());
        int num = rand() % 100;
        cout << ">>MyTask num = " << num << endl;
    }
};

void test01(){
    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4,10);
    pool.start();

    int cnt = 20;
    while(cnt--){
        pool.addTask(ptask.get());
        cout << "cnt = " << cnt << endl;
    }
    // sleep(5);
    pool.stop();
}

int main(void){
    test01();
    return 0;
}