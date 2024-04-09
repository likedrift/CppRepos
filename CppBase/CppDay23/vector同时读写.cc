#include <iostream>
#include <vector>
using namespace std;

void test01(){
    vector<int> vec;
    vec.push_back(1);

    bool flag = true;
    for(auto it = vec.begin(); it != vec.end(); ++it){
        cout << *it << " ";
        if(flag){
            // 底层发生扩容 表现为堆中开辟新的区域
            vec.push_back(2);
            flag = false;
            // 如果不重新置位，it会一直指向旧的vec空间
            // 会出现未定义行为，但是也可能会走到最后面
            // 就是当最后走到了新的区域的时候
            it = vec.begin();
        }
    }
}

int main(void){
    test01();
    return 0;
}