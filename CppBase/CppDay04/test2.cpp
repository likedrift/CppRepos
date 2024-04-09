#include <iostream>

using std::cout;
using std::endl;

class B
{
public:
    B()
    {
        cout << "B()" << endl;
    }

    ~B()
    {
        cout << "~B()" << endl;
    }

    B(const B &rhs)
    {
        cout << "B(const B&)" << endl;
    }

    B &operator=(const B &rhs)
    {
        cout << "B &operator=(const B &s)" << endl;

        return *this;
    }
};

B func(const B &rhs){
    cout << "B func(const B &)" << endl;
    return rhs;// 非引用，触发拷贝，并且不止适用于类，包括各种基本数据类型也都是一样的
}

// const B & func(const B &rhs)
// {
//     cout << "B func(const B &)" << endl;
//     return rhs;
// }

int main(int argc, char **argv)
{
    B b1, b2; // B() B()
    b2 = func(b1); // 10#   B func(const B &) --> B(const B&) --> B &operator=(const B &s)

    return 0;
}