#include <iostream>

using std::cout;
using std::endl;

void addFunc(int num1,int num2){
    cout << "num1 + num2 = " << num1 + num2 << endl;
}

int main(void){
    //FunctionPointer
    //函数指针
    void (*p)(int,int) = &addFunc;
    int num1 = 10;
    int num2 = 20;
    (*p)(num1,num2);
    return 0;
}