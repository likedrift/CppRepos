#include <iostream>

using std::cout;
using std::endl;


int main(void){
    // Pointer to array
    // 数组指针
    // 指向数组的指针，本质是一个指针，指针所指向的是数组的首地址
    int arr[5] = {10,20,30,40,50};
    int (*p)[5] = &arr;

    // 遍历数组
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]);++i){
        cout << (*p)[i] << " ";
    }
    cout << endl;
    return 0;
}