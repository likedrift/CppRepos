#include <iostream>

using std::cout;
using std::endl;

int main(void){
    // Pointer to const
    int num1 = 66;
    int num2 = 77;
    const int * p1 = &num1;
    // 也可以是
    // int const * p1 = &num1;

    // 可以修改指针指向，但不能修改指针指向的值
    //*p1 = 77; // error
    cout << *p1 << endl;

    p1 = &num2;
    cout << *p1 << endl;

    return 0;
}