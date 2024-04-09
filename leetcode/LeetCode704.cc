#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;

        while(start <= end){
            // mid每次二分查找都要重新赋值
            int mid = (end + start) / 2;
            // target小于中间值，在左半部分继续查
            if(nums[mid] > target){
                end = mid - 1;
            }else if(nums[mid] < target){
                start = mid + 1;
            }else{
                return mid;
            }
        }
        return -1;
    }
};
void test01(){

}

int main(void){
    test01();
    return 0;
}