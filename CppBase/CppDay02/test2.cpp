#include <iostream>

using std::cout;
using std::endl;

void f2(int &x, int &y)
{
    int z = x;
    x = y;
    y = z;
}

void f3(int *x, int *y)
{
    int z = *x;
    *x = *y;
    *y = z;
}

int main()
{
    int x, y;
    x = 10;
    y = 26;
    cout << "x, y = " << x << ", " << y << endl; // x, y = 10, 26
    f2(x, y); // x = 26 y = 10;
    cout << "x, y = " << x << ", " << y << endl; // x, y = 26, 10
    f3(&x, &y); // x = 10 y = 26
    cout << "x, y = " << x << ", " << y << endl; // x, y = 10, 26
    x++; // ++x  --> x = 11;
    y--; // y = 25
    f2(y, x); // int & x = y = 25; int & y = x = 11; --> y = 11 x = 25
    cout << "x, y = " << x << ", " << y << endl; // x, y = 25, 11
    return 0;
}