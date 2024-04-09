#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test01(){
    string str;
    cout << "str:" << str << endl;
    cout << "is str empty:" << str.empty() << endl;
    cout << "str's size:" << str.size() << endl;

    cout << endl;

    string str1(5,'a');
    cout << "str1:" << str1 << endl;
    cout << "is str1 empty:" << str1.empty() << endl;
    cout << "str1's size:" << str1.size() << endl;

    string str2("hello");

    cout << endl;

    string str3("aaabbbb",2);//截取前面两个字符
    cout << "str3:" << str3 << endl;

    string str4(str3);
    cout << "str4:" << str4 << endl;

    string str5 = str3;
    cout << "str5:" << str5 << endl;

    string str6 = str2 + ',' + str3;
    string str7 = str2 + ",world" + str5;
}

int main(void){
    test01();
    return 0;
}