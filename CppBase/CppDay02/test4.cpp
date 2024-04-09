#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;
    if (x++ > 5) // x++ > 5 --> 5 > 5 ? --> false  x = 6
    {
        cout << x << endl;
    }
    else
    {
        cout << x-- << endl; // cout << 6 << endl  (x--) --> x = 5
    }

    return 0;
}