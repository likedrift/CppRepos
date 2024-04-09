#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 反向双指针
        int p1 = m - 1; // nums1的最大元素位置
        int p2 = n - 1; // nums2的最大元素位置
        int tail = m + n - 1; // nums2的元素都插入nums1后，末尾元素的位置
        int cur = 0;
        while(p1 >= 0 || p2 >= 0){
            if(p1 == -1){
                cur = nums2[p2--];
            }else if(p2 == -1){
                cur = nums1[p1--];
            }else if(nums1[p1] > nums2[p2]){
                cur = nums1[p1--];
            }else{
                cur = nums2[p2--];
            }
            nums1[tail--] = cur;
        }
    }
};
void test01(){

}

int main(void){
    test01();
    return 0;
}