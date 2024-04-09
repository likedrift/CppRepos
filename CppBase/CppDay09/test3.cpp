#include <iostream>
#include <vector>
#include <string.h>
#include <limits>
using std::cout;
using std::endl;

class String 
{
public:
	String();
	String(const char *str);
	String(const String &rhs);
	~String();
	String &operator=(const String &rhs);
	String &operator=(const char *rhs);

	String &operator+=(const String &rhs);
	String &operator+=(const char *rhs);
	
	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;
	
	std::size_t size() const;
	const char* c_str() const;
	
	friend bool operator==(const String &lhs, const String &rhs);
	friend bool operator!=(const String &lhs, const String &rhs);
	
	friend bool operator<(const String &lhs, const String &rhs);
	friend bool operator>(const String &lhs, const String &rhs);
	friend bool operator<=(const String &lhs, const String &rhs);
	friend bool operator>=(const String &lhs, const String &rhs);
	
	friend std::ostream &operator<<(std::ostream &os, const String &rhs);
	friend std::istream &operator>>(std::istream &is, String &rhs);

private:
	char * _pstr;
};

// 如果不在初始化列表中进行初始化，会默认初始化为nullptr
String::String()
:_pstr(new char[1])
{
    _pstr[0] = '\0';
    cout << "String()" << endl;
}

String::String(const char *str)
:_pstr(new char[strlen(str) + 1]())
{
    strcpy(_pstr,str);
    cout << "String(const char *str)" << endl;
}

String::String(const String &rhs)
:_pstr(new char[strlen(rhs._pstr) + 1]())
{
    strcpy(_pstr,rhs._pstr);
    cout << "String(const String &rhs)" << endl;
}

String::~String(){
    if(_pstr){
        delete [] _pstr;
        _pstr = nullptr;
    }
    cout << "~String()" << endl;
}

String &String::operator=(const String &rhs){
    if(this != &rhs){
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr,rhs._pstr);
        cout << "operator=(const String&)" << endl;
    }
    return *this;
}

String &String::operator=(const char *rhs){
    // String tmp(rhs);
    // *this = tmp;
    // return *this;
    if(_pstr){
        delete [] _pstr;
        _pstr = new char[strlen(rhs) + 1]();
        strcpy(_pstr,rhs);
        cout << "operator=(const char*)" << endl;
    }
    return *this;
}

String &String::operator+=(const String &rhs){
    //如果是用一个临时的String对象来接收
    //为了避免析构的时候释放掉堆空间，要把这个对象的_pstr设为nullptr
    char *temp = new char[strlen(this->_pstr) + strlen(rhs._pstr) + 1]();
    strcpy(temp,this->_pstr);
    strcat(temp,rhs._pstr);
    delete [] _pstr;
    _pstr = temp;
    cout << "operator+=(const String &)" << endl;
    return *this;
}

String &String::operator+=(const char *rhs){
    char *temp = new char[strlen(this->_pstr) + strlen(rhs) + 1]();
    strcpy(temp,this->_pstr);
    strcat(temp,rhs);
    delete [] _pstr;
    _pstr = temp;
    cout << "operator+=(const char *)" << endl;
    return *this;
}

char &String::operator[](std::size_t index){
    if(index < strlen(_pstr)){
        return _pstr[index];
    }
    cout << "out of range" << endl;
    static char nullchar = '\0';
    cout << "operator[](std::size_t)" << endl;
    return nullchar;
}

const char &String::operator[](std::size_t index) const{
    if(index < strlen(_pstr)){
        return _pstr[index];
    }
    cout << "out of range" << endl;
    static char nullchar = '\0';
    cout << "operator[](std::size_t)" << endl;
    return nullchar;
}
// String str;
// const char &a = str[1];
// const char &a = str[1];

size_t String::size() const{
    cout << "size()" << endl;
    return strlen(_pstr);
}

const char *String::c_str() const{
    cout << "c_str()" << endl;
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs){
    cout << "operator==(const String &,const String &)" << endl;
    return strcmp(lhs._pstr,rhs._pstr);
}
bool operator!=(const String &lhs, const String &rhs){
    cout << "operator!=(const String &,const String &)" << endl;
    return !strcmp(lhs._pstr,rhs._pstr);
}
bool operator<(const String &lhs, const String &rhs){
    cout << "operator<(const String &,const String &)" << endl;
    return strcmp(lhs._pstr,rhs._pstr) < 0;
}
bool operator>(const String &lhs, const String &rhs){
    cout << "operator>(const String &,const String &)" << endl;
    return strcmp(lhs._pstr,rhs._pstr) > 0;
}
bool operator<=(const String &lhs, const String &rhs){
    cout << "operator<=(const String &,const String &)" << endl;
    return strcmp(lhs._pstr,rhs._pstr) <= 0;
}
bool operator>=(const String &lhs, const String &rhs){
    cout << "operator>=(const String &,const String &)" << endl;
    return strcmp(lhs._pstr,rhs._pstr) >= 0;
}
	
std::ostream &operator<<(std::ostream &os, const String &rhs){
    os << rhs._pstr;
    cout << "operator<<(std::ostream &,const String &)" << endl;
    return os;
}

// void readInputChar(std::istream & is,char *str){
//     cout << "please input a string" << endl;
//     while(is >> str,!is.eof()){
//         if(is.bad()){
//             cout << "istream has broken" << endl;
//             return;
//         }else if(is.fail()){
//             is.clear();
//             is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//             cout << "please input a string" << endl;
//         }else{
//             break;
//         }
//     }
// }

// 不用考虑错误输入的状态
std::istream &operator>>(std::istream &is, String &rhs){
    if(rhs._pstr){
        delete [] rhs._pstr;
        rhs._pstr = nullptr;
    }
    
    // 动态获取从键盘输入数据的长度
    std::vector<char> buffer;
    char ch;
    while((ch = is.get()) != '\n'){
        buffer.push_back(ch);
    }

    rhs._pstr = new char[buffer.size() + 1]();
    strncpy(rhs._pstr,&buffer[0],buffer.size());

    // readInputChar(is,rhs._pstr);
    cout << "operator>>(std::istream,String)" << endl;
    return is;
}


String operator+(const String &lhs, const String &rhs){
    char *ctemp = new char[strlen(lhs.c_str()) + strlen(rhs.c_str()) + 1]();
    strcpy(ctemp,lhs.c_str());
    strcat(ctemp,rhs.c_str());
    String temp(ctemp);
    delete [] ctemp;
    cout << "operator+(const String &,const String &)" << endl;
    return temp;
}
String operator+(const String &lhs, const char *rhs){
    char *ctemp = new char[strlen(lhs.c_str()) + strlen(rhs) + 1]();
    strcpy(ctemp,lhs.c_str());
    strcat(ctemp,rhs);
    String temp(ctemp);
    delete [] ctemp;
    cout << "operator+(const String &,const char *)" << endl;
    return temp;
}
String operator+(const char *lhs, const String &rhs){
    char *ctemp = new char[strlen(lhs) + strlen(rhs.c_str()) + 1]();
    strcpy(ctemp,lhs);
    strcat(ctemp,rhs.c_str());
    String temp(ctemp);
    delete [] ctemp;
    cout << "operator+(const char *,const String &)" << endl;
    return temp;
}

void test01(){
    // 测试默认构造函数
    String s1;
    
    // 测试带参数的构造函数
    String s2("Hello");
    String s3 = "World";
    
    // 测试拷贝构造函数
    String s4 = s2;
    
    // 测试赋值运算符
    s1 = s2;
    s1 = "New String";
    
    // 测试 += 运算符
    s1 += s2;
    s1 += " World";
    
    // 测试下标运算符
    char ch = s1[0];
    const char &ch2 = s1[10];
    
    // 测试 size 和 c_str 函数
    std::size_t len = s1.size();
    const char *cstr = s1.c_str();
    
    // 测试比较运算符
    bool isEqual = (s1 == s2);
    bool isNotEqual = (s1 != s2);
    bool isLess = (s1 < s2);
    bool isGreater = (s1 > s2);
    bool isLessOrEqual = (s1 <= s2);
    bool isGreaterOrEqual = (s1 >= s2);
    
    // 测试输出运算符
    std::cout << s1 << std::endl;
    
    // 测试输入运算符
    std::cin >> s1;
}

int main(void){
    test01();
    return 0;
}