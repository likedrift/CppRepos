#include <iostream>

using std::cout;
using std::endl;

namespace MySpace{
    void swap(int & num1,int & num2){
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
