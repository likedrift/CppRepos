#include <iostream>

using std::cout;
using std::endl;

int main(void){
    // Const pointer
    int num1 = 77;
    int num2 = 88;
    
    // 可以修改指针指向的值，但是不能修改指针的指向
    int * const p1 = &num1;
    //p1 = &num2; // error
    cout << *p1 << endl;

    *p1 = num2;
    cout << *p1 << endl;

    return 0;
}