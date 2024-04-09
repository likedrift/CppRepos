#include <iostream>

using std::cout;
using std::endl;

namespace MySpace{
    extern void swap(int & num1,int & num2);
}

int main(void){
    int num1 = 10;
    int num2 = 20;
    cout << "before swap:num1 = " << num1 << ",num2 = " << num2 << endl;
    MySpace::swap(num1,num2);
    cout << "after swap:num1 = " << num1 << ",num2 = " << num2 << endl;

    return 0;
}