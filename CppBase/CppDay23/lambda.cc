#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

void func(int & value){
    ++value;
    cout << value << " ";
}

void test01(){
    vector<int> vec{1,2,3,4,5};
    copy(vec.begin(),vec.end(),
        ostream_iterator<int>(cout," "));
    cout << endl;

    for_each(vec.begin(),vec.end(),func);
    // 如果实现和声明分离 不知道func内部的做了什么怎么办?
    // lambda表达式 ---> 匿名函数 此处为 []...
    // 没有返回类型
    // []捕获列表 ()函数的参数列表 {}函数的函数体
    for_each(vec.begin(),vec.end(),[](int &value){// [] 不能不写
        ++value;
        cout << value << " ";
    });

    cout << endl;

    copy(vec.begin(), vec.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test02(){
    // 如果想把函数就近地实现出来，避免去找相关函数的实现
    // 就可以使用lambda表达式

    int a = 100;

    // 调用匿名函数
    []()->void{ // 返回值的显式表现方式： ->return type
        cout << "hello" << endl;
    }();
    // 大括号后带上() 表示调用这个函数

    // 想使用局部变量的话，在[]内捕获
    [a]()->void{
        // ++a; // 传入的是const版本，不能被修改
        cout << "a = " << a << endl;
    }();


    // 想修改局部变量的话
    // lambda表达式默认是const的，想修改可以使用mutable
    [a]()mutable->void{ // 这里的a是拷贝的一份，值捕获
        ++a;
        cout << "a = " << a << endl; // 101
    }();

    cout << "a = " << a << endl; // 上面是值传递，这里还是100

    [&a]() mutable -> void { // 引用捕获
        ++a;
        cout << "a = " << a << endl; // 101
    }();
    cout << "a = " << a << endl; // 上面引用传递，这里是101
}

void test03(){
    [](const string &name){
        cout << "name = " << name << endl;
    }("wangdao");

    auto f = [](const string &name){
        cout << "name = " << name << endl;
    };
    f("test");

    cout << endl << endl;

    // 函数指针
    typedef void (*pFunc)(const string &);// C的方法
    // typedef void (*)(const string &) pFunc;
    // using pFunc = void(const string &);// C++的方法
    pFunc pf = [](const string &name){
        cout << "name = " << name << endl;
    };
    pf("wangdao");
}

void test04(){
    int num = 10;
    string name("wangdao");
    [num, name](const string &value){
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "value = " << value << endl;
    }("hello");
    
    [&num, name](const string &value){
        ++num;
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "value = " << value << endl;
    }("hello");
    [&num, &name](const string &value){
        ++num;
        name = "wuhan";
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "value = " << value << endl;
    }("hello");

    // [=,&num]表示
    // 除了num用引用传递，其他变量全部用值传递
    [=, &num](const string &value){

    }("hello");

    // num使用值传递，其他变量使用引用传递
    [&,num](const string & value){

    }("hello");
    
    // 如果是全局变量，可以不用捕获，直接使用
    // 捕获的作用域是当前的函数

    // 不要捕获局部变量的引用

}

int globalVar = 10;
void test05(){
    []()->void{
        ++globalVar;
        cout << globalVar << endl;
    }();

    cout << globalVar << endl;
    
}

int main(void){
    test05();
    return 0;
}