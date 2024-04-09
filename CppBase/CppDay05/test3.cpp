#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String{
public:
    // 无参构造
	// String() = default;
    String(): _pstr(new char[1]()){}
    // 有参构造
	String(const char *pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr,pstr);
        cout << "String(const char *pstr)" << endl;
    }
    // 拷贝构造
	String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr,rhs._pstr);
        cout << "String(const String &rhs)" << endl;
    }
    // 赋值运算符函数
	String &operator=(const String &rhs){
        if(this != &rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr,rhs._pstr);
            cout << "String &operator=(const String &)" << endl;
        }
    }
    // 析构函数
	~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
            cout << "~String()" << endl;
        }
    }

	void print(){
        cout << "_pstr = " << _pstr << endl;
    }
    // 字符串长度
    size_t length() const{
        return strlen(_pstr);
    }
    // 后面的const修饰的是成员函数本身，表明该函数不会修改类的任何成员变量，也就是说它是常量成员函数
    const char * c_str() const{
        return _pstr;
    }

private:
	char * _pstr;
};

int main(){
    String str;
    str.print();
	// String str1("Tom");
	// str1.print();
	
    //const char * p = str1.c_str();
    //char arr[20] = {0};
    //strcpy(arr,str1.c_str()); 

	// String str2 = "Hello,world";
	// String str3("wangdao");
	
	// str2.print();		
	// str3.print();	
	
	// String str4 = str3;
	// str4.print();
	
	// str4 = str2;
	// str4.print();
	
	return 0;
}