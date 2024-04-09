#include <iostream>

using std::cout;
using std::endl;

class MyClass{
public:
    void memberFunction(int x){
        cout << "void memberFunction(int x), x = " << x << endl; 
    }
};

// 定义成员函数指针类型
typedef void (MyClass::*MemberFunctionPointer)(int);

void test01(){
    // 获取成员函数指针
    MemberFunctionPointer mfp = &MyClass::memberFunction;
    // 使用成员函数指针调用成员函数
    MyClass obj1;
    (obj1.*mfp)(20);
    
    MyClass *obj2 = new MyClass();
    (obj2->*mfp)(30);
}

int main(void){
    test01();
    return 0;
}