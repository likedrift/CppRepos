#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

class Singleton {
    Singleton(int x,int y)
    : _ix(x)
    , _iy(y)
    {
        cout << "Singleton(int,int)" << endl;
    }

    ~Singleton(){
        cout << "~Singleton()" << endl;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    //C++11之后的写法
    //表示从这个类中删除这个函数
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton& rhs) = delete;

public:
    static Singleton * getInstance(){
        pthread_once(&_once,init_r);
        return _pInstance;
    }

    static void init_r(){
        _pInstance  = new Singleton(1,2);
        atexit(destroy);
    }

    void init(int x,int y){
        _ix = x;
        _iy = y;
    }

	void print()
	{
		cout << "(" << this->_ix 
            << "," << this->_iy
			<< ")" << endl;
	}
private:
	int _ix;
	int _iy;
    static Singleton * _pInstance;
    static pthread_once_t _once;
};
//饱汉式，初始化成空指针，懒加载
/* Singleton * Singleton::_pInstance = nullptr; */
//饿汉式，初始化时就创建出单例对象
Singleton * Singleton::_pInstance = getInstance();

pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test0()
{
    Singleton::getInstance()->print();
    Singleton::getInstance()->print();
    Singleton::getInstance()->print();
    Singleton::getInstance()->print();
    /* Singleton::destroy(); */
    Singleton::getInstance()->print();
    
}

int main(void){
    test0();
    return 0;
}
