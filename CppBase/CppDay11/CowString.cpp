#include <string.h>
#include <iostream>
using namespace std;

class CowString{
    class CharProxy{
    public:
        CharProxy(CowString & self, size_t idx)
        :_self(self)
        ,_idx(idx)
        {           
        }

        operator char(){
            cout << "operator char()" << endl;
            return _self._pstr[_idx];
        }

        char & operator=(char ch);

    private:
        CowString & _self;
        size_t _idx;
    };
public:
    CowString();
    ~CowString();
    CowString(const CowString &rhs);
    CowString(const char *pstr);
    CowString & operator=(const CowString &rhs);
    CharProxy operator[](size_t idx);
    const char * c_str() const{
        return _pstr;
    }
    size_t size() const{
        return strlen(_pstr);
    }
    int use_count(){
        return *(int*)(_pstr - kRefcountLength);
    }
    friend ostream & operator <<(ostream & os, const CowString & rhs);
private:
    char * malloc(const char * pstr = ""){
        return new char[strlen(pstr) + kRefcountLength + 1]() + kRefcountLength; 
    }
    
    void release(){
        decreaseRefcount();
        if(use_count() == 0){
            delete [] (_pstr - kRefcountLength);
            _pstr = nullptr;
            cout << "delete heap" << endl;
        }
    }

    void initRefcount(){
        *(int*)(_pstr - kRefcountLength) = 1;
    }

    void increaseRefcount(){
        ++*(int*)(_pstr - kRefcountLength);
    }

    void decreaseRefcount(){
        --*(int*)(_pstr - kRefcountLength);
    }

private:
    static const int kRefcountLength = 4;
    char * _pstr;
};

ostream & operator <<(ostream & os, const CowString & rhs){
    os << rhs._pstr;
    return os;
}

CowString::CowString()
:_pstr(malloc())
{
    cout << "CowString()" << endl;
    initRefcount();
}

CowString::~CowString(){
    release();
}

CowString::CowString(const CowString & rhs)
:_pstr(rhs._pstr)
{
    increaseRefcount();
    cout << "CowString(const CowString &)" << endl;
}

CowString::CowString(const char * str)
:_pstr(malloc(str))
{
    cout << "CowString(const char *)" << endl;
    strcpy(_pstr,str);
    initRefcount();
}

CowString & CowString::operator=(const CowString & rhs){
    if(this != &rhs){
        cout << "CowString & operator=(const CowString &)" << endl;
        release();
        _pstr = rhs._pstr;
        increaseRefcount();
    }
    return *this;
}

CowString::CharProxy CowString::operator[](size_t idx){
    return CharProxy(*this,idx);
}

char & CowString::CharProxy::operator=(char ch){
    if(_idx < _self.size()){
        if(_self.use_count() > 1){
            _self.decreaseRefcount();
            char * ptemp = _self.malloc(_self._pstr);
            strcpy(ptemp,_self._pstr);
            _self._pstr = ptemp;
            _self.initRefcount();
        }
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

void test01(){
    CowString str1("hello");
    CowString str2(str1);
    CowString str3(str1);
    


    cout << str1[0] << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << str3.use_count() << endl;

    str1[0] = 'H';

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << str3.use_count() << endl;

    str1[0] = 'X';
    cout << str1 << endl;
    cout << str1[0] << endl;
    std::string(5,str1[0]);
}

int main(void){
    test01();
    return 0;
}