#include <iostream>

using namespace std;

// 函数模板
template <class T1,class T2>
T1 add(T1 a, T2 b){
    return a + b;
}

template <class T, int kBase = 10>
T sub(T a){
    return a - kBase;
}



// template <class T1,class T2>
// T2 add(T1 a, T2 b){
//     return a + b;
// }

// 类模板
template <class T>
class MyClass{
public:
    MyClass(T x, T y)
    :_x(x)
    ,_y(y)
    {
        cout << "MyClass(T, T)" << endl;
    }
    
    T getX() const {
        return _x;
    }

    T getY() const {
        return _y;
    }
private:
    T _x;
    T _y;
};

void test01(){
    auto addSum1 = add(1.5,2);
    auto addSum2 = add(2,1.5);
    cout << addSum1 << endl;
    cout << addSum2 << endl;

    cout << add<double>(1.5,2) << endl;
    cout << add<int>(1.5,2) << endl;

    auto sub1 = sub(5);
    cout << sub1 << endl;

    MyClass<int> myClass1(2,3);
    cout << "(" << myClass1.getX() << "," << myClass1.getY() << ")" << endl;
    MyClass<double> myClass2(1.5,6.2);
    cout << "(" << myClass2.getX() << "," << myClass2.getY() << ")" << endl;
};

int main(void){
    test01();
    return 0;
}