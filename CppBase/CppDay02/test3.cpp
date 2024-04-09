#include <iostream>
using std::cout;
using std::endl;

int foo(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 1;
    return 3 * foo(x - 1, y / 2);
}

// 3 * foo(2,2)
// 3 * 3 * foo(1,1)
// 3 * 3 * 3 * foo(0,0)
// 3 * 3 * 3 * 1
// --> 27

int main()
{
    cout << foo(3, 5) << endl;
}