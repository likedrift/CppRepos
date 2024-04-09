#include <iostream>
#include <vector>
#include <limits>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minLength = std::numeric_limits<int>::max();
        int start = 0;
        int windowLength = 0;
        int sum = 0;

        for(int currPos = 0; currPos < nums.size(); ++currPos){
            sum += nums[currPos];
            // 当已经找到总和大于等于target的数组时
            while(sum >= target){
                windowLength = currPos - start + 1; // 当前满足条件时，滑动窗口的长度
                // 更新长度最小的子数组长度
                minLength = windowLength < minLength ? windowLength : minLength;
                // 滑动窗口的起始索引往后移动，同时也删除掉了之前起始索引对应的值，继续寻找长度最小的连续子数组
                sum -= nums[start++];
            }
        }
        
        return minLength == std::numeric_limits<int>::max() ? 0 : minLength;
    }
};

void test01(){

}

int main(void){
    test01();
    return 0;
}