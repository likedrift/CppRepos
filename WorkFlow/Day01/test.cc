#include <workflow/WFFacilities.h>
#include <signal.h>
#include <iostream>

using std::cout;
using std::endl;

static WFFacilities::WaitGroup wait_group(3);
// wait_group的参数用来表示有多少个任务还没完成
void sig_handler(int signo)
{
    cout << "signo = " << signo << endl;
    wait_group.done();
    // done方法表示完成了一个任务
}
int main()
{
    signal(SIGINT, sig_handler);
    wait_group.wait();
    // wait方法当存在至少一个任务未完成时，线程阻塞。
    return 0;
}