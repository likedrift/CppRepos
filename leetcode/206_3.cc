#include <iostream>

using std::cout;
using std::endl;
struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *listReverse(ListNode *prev, ListNode *curr){
    // 递归出口
    if(curr == nullptr){
        return prev;
    }

    ListNode *temp = curr->next;
    curr->next = prev;
    // prev = curr;
    // curr = temp;
    
    return listReverse(curr, temp);
}

class Solution{
public:
    ListNode *reverseList(ListNode *head){
        return listReverse(nullptr, head);
    }
};
