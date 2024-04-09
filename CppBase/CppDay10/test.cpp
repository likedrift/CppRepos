#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Singleton{
private:
    class AutoRelease{
    public:
        AutoRelease(){
            cout << "AutoRelease()" << endl;
        }

        ~AutoRelease(){
            cout << "~AutoRelease()" << endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
        
    };
private:
    Singleton(int real, int image,const char *str)
    :_str(new char[strlen(str) + 1]())
    ,_real(real)
    ,_image(image)
    {
        strcpy(_str,str);
        cout << "Singleton(int, int,char *)" << endl;
    }
    ~Singleton(){
        cout << "~Singleton()" << endl;
        if(_str){
            delete [] _str;
            _str = nullptr;
        }
    }

    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
public:
    friend class AutoRelease;

    static Singleton * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Singleton(3,4,"hello");
        }
        return _pInstance;
    }
    
    void init(int real, int image){
        _real = real;
        _image = image;
    }

    void print(){
        cout << "[" << _real << "+" << _image << "i"  << "_str:" << _str << "]" << endl;
    }

private:
    int _real;
    int _image;
    char *_str;
    static Singleton * _pInstance;
    static AutoRelease _ar;
};
Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;

void test01(){
    Singleton::getInstance();
    Singleton::getInstance()->print();
}

int main(void){
    test01();
    return 0;
}