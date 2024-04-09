#include <iostream>

using std::cout;
using std::endl;

namespace owo{
    extern int num1;
    extern void func();
}


int main(void){
    using owo::func;
    using owo::num1;
    func();
    cout << num1 << endl;
    return 0;
}