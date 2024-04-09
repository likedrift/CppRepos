#include <iostream>

using std::cout;
using std::endl;


int main(void){
    // Array of pointers
    // 指针数组
    int num1 = 10,num2 = 20,num3 = 30,num4 = 40,num5 = 50;
    //int *p1 = &num1,*p2 = &num2,*p3 = &num3,*p4 = &num4,*p5 = &num5;
    // 数组内的每个元素都是指针类型
    int *p[5] = {&num1,&num2,&num3,&num4,&num5};

    // 遍历数组
    for(int i = 0; i < sizeof(p)/sizeof(p[0]);++i){
        cout << *p[i] << " ";  
    }
    cout << endl;
    return 0;
}