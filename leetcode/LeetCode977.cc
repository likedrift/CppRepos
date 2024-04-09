#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::endl;
using std::vector;

    class Solution {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            // bool zeroFlag = false;
            // int zeroPos = 0;
            // for(int i = left; i < right; ++i){
            //     if(!zeroFlag && nums[i] == 0){
            //         zeroFlag = true;
            //         zeroPos = i;
            //     }
            //     if(nums[i]){
            //         nums[i] = pow(nums[i], 2);
            //     }
            // }

            // if(zeroPos == 0){
            //     newArr = nums;
            // }else{
            //     // 双指针
            // }

            int left = 0;
            int right = nums.size() - 1;

            vector<int> newArr(nums.size());
            int pos = nums.size() - 1;
            while(pos >= 0 && left <= right){
                if(pow(nums[left],2) >= pow(nums[right],2)){
                    newArr[pos--] = pow(nums[left++], 2);
                }else if(pow(nums[left],2) < pow(nums[right],2)){
                    newArr[pos--] = pow(nums[right--], 2);
                }
            }
            return newArr;
        }
    };
void test01(){

}

int main(void){
    test01();
    return 0;
}