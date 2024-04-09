#include <iostream>

using std::cout;
using std::endl;
using std::cin;

void test01(){
    int num = 0;
    cout << cin.good() << endl;
    cout << cin.bad() << endl;
    cout << cin.fail() << endl;
    cout << cin.eof() << endl;

    cout << endl;
    cin >> num;
    cout << cin.good() << endl;
    cout << cin.bad() << endl;
    cout << cin.fail() << endl;
    cout << cin.eof() << endl;

    cout << "num:" << num << endl;
}

int main(void){
    test01();
    return 0;
}