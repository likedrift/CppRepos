#include <iostream>
#include <string.h>
using namespace std;

class String{
public:

    // 无参构造
    String():_pstr(new char[1]()){
        cout << "String()" << endl;
    }

    // 有参构造
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]()){
        strcpy(_pstr,pstr);
        cout << "String(const char *)" << endl;
    }

    // 拷贝构造
    String(const String & rhs)
    :_pstr(new char[strlen(rhs.c_str()) + 1]())
    {
        strcpy(_pstr,rhs.c_str());
        cout << "String(const String &)" << endl;
    }

    // 赋值
    String & operator=(const String & rhs){
        if(this != &rhs){
            delete [] _pstr;
            // 深拷贝
            _pstr = new char[strlen(rhs.c_str()) + 1];
            strcpy(_pstr,rhs.c_str());
            cout << "String & operator=(const String &)" << endl;
        }
        return *this;
    }

    // 移动构造
    String(String && rhs)
    :_pstr(rhs._pstr)
    {
        rhs._pstr = nullptr;
        cout << "String(String &&)" << endl;
    }

    // 移动赋值
    String & operator=(String && rhs){
        if(this != &rhs){
            delete [] _pstr;
            // 浅拷贝
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
            cout << "String & operator=(string &&)" << endl;
        }
        return *this;
    }

    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
        cout << "~String()" << endl;
    }

    void print(){
        cout << _pstr << endl;
    }

size_t length() const {
    return strlen(_pstr);
}

const char * c_str() const {
    return _pstr;
}

private:
    char *_pstr;
};

void test01(){
    // String s1 = "hello";
    // s1.print();
    // String s2(s1);
    // s2.print();
    // String s3("hello");
    // s3.print();
    // s2 = s3;
    // s2.print();

    String s1("hello");
    String s2(std::move(s1));
    String s3 = "hello";
    s1 = String("world");
}

int main(void){
    test01();
    return 0;
}