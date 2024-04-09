#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int length = pow(n, 2);
        vector<vector<int>> vec(length);
        // for(int i = 1; i <= length; ++i)
        for(int i = 0; i < n; ++i){
            // 如果是第一个vector和最后一个vector，都是要直接填满的
            // 并且每个vector最后一个元素按顺序赋值
        }
    }
};
void test01(){

}

int main(void){
    test01();
    return 0;
}