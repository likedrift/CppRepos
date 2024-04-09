#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;

// 完成输入一个整型数据
void inputInteger(int num){
    // ctrl+D cin会检测已经到达文件尾(eof) 此时cin.eof()会返回true !cin.eof()就为false 
    // 或者真的到达了文件尾，结果同上
    while(cin >> num, !cin.eof()){
        if(cin.bad()){
            cout << "cin has broken" << endl;
            return;
        }else if(cin.fail()){
            // fail置位，是可以修改的错误
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "请输入一个int类型数据:" << endl;
        }else{
            cout << "num:" << num << endl;
        }
    }
}


void test01(){
    int num = 0;
    inputInteger(num);
}

int main(void){
    test01();
    return 0;
}