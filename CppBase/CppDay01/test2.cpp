#include <iostream>

using std::cout;
using std::endl;

namespace owo{
    int num1 = 10;
    void func(){
        cout << "test2.cpp , num1 = " << num1 << endl;
    }
}

void test01(){
    owo::func();
}
