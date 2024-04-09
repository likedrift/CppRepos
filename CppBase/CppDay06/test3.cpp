#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test01(){
    // 存放int数据的vector
    // 调用函数存放数据
    vector<int> nums1;
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(3);
    nums1.push_back(4);
    nums1.push_back(5);
    // for(auto & num : nums1){
    //     cout << num << endl;
    // }
    
    // 直接初始化
    vector<int> nums2{6,7,8,9,10};
    
    // 传入一个参数初始化，代表vector的元素个数
    vector<int> nums3(5);

    // 传入两个参数初始化，第一个参数为vector元素个数，第二个参数为初始化的默认值
    vector<int> nums4(5,1);

    // 传入数组初始化
    int arr[5] = {11,21,31,41,51};
    vector<int> nums5(&arr[0],&arr[5]); // 左闭右开区间

    // 传入迭代器初始化
    vector<int> nums6(nums2.begin(),nums2.end() - 2);

    // 存放int数据的vector的vector
    vector<vector<int>> v;
    v.push_back(nums1);
    v.push_back(nums2);
    v.push_back(nums3);
    v.push_back(nums4);
    v.push_back(nums5);
    v.push_back(nums6);

    // 遍历
    // 1 2 3 4 5
    // 6 7 8 9 10
    // 0 0 0 0 0
    // 1 1 1 1 1
    // 11 21 31 41 51
    // 6 7 8
    for(vector<vector<int>>::iterator it1 = v.begin(); it1 != v.end(); it1++){
        for(vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
            cout << *it2 << " ";
        }
        cout << endl;
    }
}

int main(void){
    test01();
    return 0;
}