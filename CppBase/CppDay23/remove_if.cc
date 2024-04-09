#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool func(int value){
    return value > 4;
}
void test01(){
    vector<int> vec = {1,4,6,8,9,2};
    for_each(vec.begin(),vec.end(),[](int &value){
        cout << value << " ";
    });
    cout << endl;

    // remove_if不能将满足条件的元素一次性删除
    // 需要配合erase使用
    // 此时it指向了最后一个没有被删除的元素
    // 使用erase把it和it之后的所有元素都删除就可
    // auto it = remove_if(vec.begin(),vec.end(),func);
    auto it = remove_if(vec.begin(),vec.end(),
                    [](int value){return value > 4;});
    vec.erase(it,vec.end());

    
}

int main(void){
    test01();
    return 0;
}