#include <iostream>

using std::cout;
using std::endl;

class Base{
public:
    Base(int val)
    :_val(val)
    {
        //cout << "Base(int)" << endl;
    }

    friend
    Base operator+(const Base & lhs, const Base & rhs);
    bool operator==(const Base & rhs) const{
        return this->_val == rhs._val;
    }
private:
    int _val;
};

Base operator+(const Base & lhs, const Base & rhs){
    return Base(rhs._val - lhs._val);
}


void test01(){
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);
    cout << (x + y == j - i) << endl;
}

int main(void){
    test01();
    return 0;
}