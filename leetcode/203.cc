#include <iostream>

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution{
public:

    ListNode *removeElements(ListNode *head, int val){
        // 删除头结点
        while(head != nullptr && head->val == val){
            ListNode *tmp = head;
            head = head->next;
            delete tmp;
        }


        // 删除非头结点
        ListNode *cur = head;
        while(cur != nullptr && cur->next != nullptr){
            ListNode *tmp = cur;
            if(cur->next->val == val){
                tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }else{
                cur = cur->next;
            }
        }
        return head;
    }
};