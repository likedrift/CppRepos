#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

class CowString{
    class ForCopy{
    public:

        char & operator=(char ch);
        friend ostream & operator<<(ostream & os, const ForCopy & rhs);
        ForCopy(char str)
        :_str(str)
        {
            cout << "ForCopy(char)" << endl;
        }
        
        ~ForCopy(){
            cout << "~ForCopy()" << endl;
        }

    private:
        char _str;
        CowString & _self;
        size_t _idx;
    };
public:
    CowString();
    ~CowString();
    CowString(const CowString & rhs);
    CowString(const char * pstr);
    CowString & operator=(const CowString & rhs);
    ForCopy operator[](size_t idx);
    const char * c_str() const{
        return _pstr;
    }
    size_t size() const{
        return strlen(_pstr);
    }
    int use_count() {
        return *(int*)(_pstr - kRefCountLength);
    }
    friend ostream & operator<<(ostream & os, const CowString & rhs);
    friend class ForCopy;
private:
    char * malloc(const char * pstr = nullptr){
        if(pstr){
            return new char[kRefCountLength + strlen(pstr) + 1]() + kRefCountLength;
        }else{
            return new char[kRefCountLength + 1]() + kRefCountLength;
        }
    }

    void release(){
        decreaseRefCount();
        if(use_count() == 0){
            delete [] (_pstr - kRefCountLength);
            _pstr = nullptr;
            cout << "delete heap" << endl;
        }
    }

    void initRefCount(){
        *(int *)(_pstr - kRefCountLength) = 1;
    }

    void increaseRefCount(){
        ++*(int *)(_pstr - kRefCountLength);
    }

    void decreaseRefCount(){
        --*(int *)(_pstr - kRefCountLength);
    }

private:
    static const int kRefCountLength = 4;//sizeof(int):4
    char *_pstr;
};

ostream & operator<<(ostream & os, const CowString & rhs){
    os << rhs._pstr;
    return os;
}

CowString::CowString()
:_pstr(malloc())
{
    cout << "CowString()" << endl;
    initRefCount();
}

CowString::~CowString(){
    release();
}

// 浅拷贝，指向同一片堆空间
CowString::CowString(const CowString & rhs)
:_pstr(rhs._pstr)
{
    increaseRefCount();
    cout << "CowString(const CowString &)" << endl;
}

// 深拷贝，申请新的堆空间存放传入的字符串
// 因此也需要初始化新的引用计数.
CowString::CowString(const char * pstr)
:_pstr(malloc(pstr))
{
    cout << "CowString(const char *)" << endl;
    strcpy(_pstr,pstr);
    initRefCount();
}

CowString &CowString::operator=(const CowString &rhs){
    if(this != &rhs){
        cout << "CowString &operator=(const CowString &)" << endl;
        // 将自己指向的堆空间区域 引用计数-1
        release();
        _pstr = rhs._pstr;
        increaseRefCount();
    }
    return *this;
}

// char & CowString::operator[](size_t idx){
//     if(idx < size()){
//         return _pstr[idx];
//     }else{
//         // 处理越界
//         cout << "out of range" << endl;
//         static char nullchar = '\0';
//         return nullchar;
//     }
// }

// 不加引用
CowString::ForCopy CowString::operator[](size_t idx){
    if(use_count() > 1){
        char * newStr = new char[strlen(_pstr) + 1]();
        strcpy(newStr,_pstr);
        decreaseRefCount();
        initRefCount();
        _pstr = newStr;
    }
    return ForCopy(_pstr[idx]);
}

char & CowString::ForCopy::operator=(char ch){

}

// ostream & CowString::ForCopy::operator<<(ostream & os, const ForCopy & rhs){

// }


void test01(){

}

int main(void){
    test01();
    return 0;
}