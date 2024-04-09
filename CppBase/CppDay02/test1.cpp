#include <iostream>

using std::cout;
using std::endl;

int & func(){
    int *num1 = new int(10);
    return *num1;
}

void test01(){
    cout << func() << endl;
    cout << &func() << endl;
}

int main(void){
    test01();
    return 0;
}