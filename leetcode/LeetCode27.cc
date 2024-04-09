#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;
        int size = nums.size();

        while (left <= right){
            if(nums[left] == val){
                // 把后面的元素往前覆盖，并且size--
                for(int i = left; i < size - 1; ++i){
                    nums[i] = nums[i + 1];
                }
                size--;
                right--;
                continue;
            }else if(nums[right] == val){
                for(int j = right; j < size - 1; ++j){
                    nums[j] = nums[j + 1];
                }
                size--;
                right--;
                continue;
            }
            right--;
            left++;
        }
        return size;
    }
};

void test01(){
    vector<int> nums{0,1,2,2,3,0,4,2};
    Solution solution;
    int val = 2;
    int size = solution.removeElement(nums,val); 
    cout << size << endl;
}

int main(void){
    test01();
    return 0;
}