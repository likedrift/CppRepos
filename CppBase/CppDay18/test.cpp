#include <iostream>
#include <vector>
#include <deque>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

void test01(){
    /**
     * vector
    */
    // 无参
    vector<int> v1;
    // count个value
    vector<int> v2(10, 100);
    // 固定个数的默认值
    vector<int> v3(10);
    // 迭代器范围
    int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v4(arr1,arr1+10);
    // 大括号
    vector<int> v5{10,20,30,40,50};
    
    // 遍历v5
    for(size_t idx = 0; idx != v5.size(); ++idx){
        cout << v5[idx] << " ";
    }
    cout << endl;

    vector<int>::iterator it = v5.begin();
    for(;it != v5.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    for(auto & elem : v5){
        cout << elem << " ";
    }
    cout << endl;

    /**
     * deque
    */
    // 无参
    deque<int> d1;
    // count个value
    deque<int> d2(5,10);
    // 固定个数的默认值
    deque<int> d3(10);
    // 迭代器范围
    int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    deque<int> d4(arr2,arr2+10);
    // 大括号
    deque<int> d5{10,20,30,40,50};

    // 遍历d2
    for(size_t idx = 0; idx != d2.size(); ++idx){
        cout << d2[idx] << " ";
    }
    cout << endl;

    deque<int>::iterator it2 = d2.begin();
    for(;it2 != d2.end(); ++it2){
        cout << *it2 << " ";
    }
    cout << endl;

    for(auto & elem : d2){
        cout << elem << " ";
    }
    cout << endl;
    /**
     * list
    */

    // 无参
    list<int> l1;
    // count个value
    list<int> l2(10, 100);
    // 固定个数的默认值
    list<int> l3(10);
    // 迭代器范围
    int arr3[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> l4(arr3,arr3+10);
    // 大括号
    list<int> l5{10,20,30,40,50};

    // 遍历l4
    list<int>::iterator it3 = l4.begin();
    for(;it3 != l4.end(); ++it3){
        cout << *it3 << " ";
    }
    cout << endl;

    for(auto & elem : l4){
        cout << elem << " ";
    }
    cout << endl;
}

int main(void){
    test01();
    return 0;
}