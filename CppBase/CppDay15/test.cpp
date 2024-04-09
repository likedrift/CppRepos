#include <iostream>

using namespace std;

double add(){
    return 0.0;
}
double add(int val){
    return val;
}

double add(double val){
    return val;
} 

template <class T,class ...Args>
double add(T x, Args ...args){
    return x + add(args...);
}
void test01(){
    int sumAdd = add(1,2.5,3,4.5,5);
    cout << sumAdd << endl;
}

int main(void){
    test01();
    return 0;
}