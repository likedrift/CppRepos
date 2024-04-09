#include <iostream>

using std::cout;
using std::endl;


class Add{
public:
    int operator()(){
        cout << "int operator()()" << endl;
        return 1;
    }

    int operator()(int a, int b){
        cout << "int operator()(int,int)" << endl;
        return a + b;
    }
};

void test01(){
    Add add;
    int result1 = add();
    int result2 = add(3,4);
    cout << "result1 = " << result1 << endl;
    cout << "result2 = " << result2 << endl;
}

int main(void){
    test01();
    return 0;
}