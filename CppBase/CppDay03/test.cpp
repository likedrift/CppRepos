#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer
{
public:
    void setBrand(const char *brand){
        strcpy(_brand,brand);
    }

    // 不推荐使用
    char *getBrand(){
        return _brand;
    }

    void setPrice(float price){
        _price = price;
    }
    
    // 不推荐使用
    float getPrice(){
        return _price;
    }

private:
    char _brand[20];
    float _price;
};

class A{
    char _arr[20];
};

void test0(){
    A a;
}

int main(void){
    return 0;
}