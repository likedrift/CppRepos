#include <iostream>

using std::cout;
using std::endl;

class Point{
private:
    Point(int x, int y)
    :_ix(x)
    ,_iy(y)
    {
        cout << "Point(int, int)" << endl;
    }
    ~Point(){
        cout << "~Point()" << endl;
    }


    //防止拷贝
    //delete拷贝构造函数和赋值运算符函数
    Point(const Point & rhs) = delete;
    Point & operator=(const Point & rhs) = delete;
public:

    static Point * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Point(1,2);
        }
        return _pInstance;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void setX(int x){
        // _pInstance->_ix = x;
        this->_ix = x;
    }

    void setY(int y){
        // _pInstance->_iy = y;
        this->_iy = y;
    }

    // static void setX(int x){
    //     if(_pInstance != nullptr){
    //         _pInstance->_ix = x;
    //     }
    // }

    // static void setY(int y){
    //     if(_pInstance != nullptr){
    //         _pInstance->_iy = y;
    //     }
    // }

    void print(){
        cout << "(" << this->_ix << "," << this->_iy << ")" << endl;
    }
private:
    int _ix;
    int _iy;
    static Point *_pInstance;
};
// 静态数据成员的初始化放在类外，紧贴类的定义
Point *Point::_pInstance = nullptr;
// int Point::_ix = 1;
// int Point::_iy = 2;

void test01(){
    Point::getInstance()->print();

    Point::getInstance()->setX(10);
    Point::getInstance()->setY(20);
    Point::getInstance()->print();

    Point::destroy();
    //delete Point::getInstance();
}

int main(void){
    test01();
    return 0;
}