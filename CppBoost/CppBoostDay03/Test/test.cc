#include <iostream>

class NonCopyable{
protected:
    NonCopyable(){}
    ~NonCopyable(){}
private:
    NonCopyable(const NonCopyable &rhs) = delete;
    NonCopyable &operator=(const NonCopyable &rhs) = delete;
};

class Derived : public NonCopyable{
public:
    Derived(int val) : data(val) {}

    void setData(int val) {
        data = val;
    }

    int getData() const {
        return data;
    }

private:
    int data;
};

int main(){
    // Derived d1(20);
    // Derived d2(10);
    // 尝试进行拷贝
    // Derived d3 = d2;
    // 尝试进行赋值
    // d2 = d1;
} 