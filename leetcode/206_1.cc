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

class Solution{
public:
    ListNode *reverseList(ListNode *head){
        // 如果链表为空
        if(head == nullptr){
            return head;
        }

        // 链表不空
        // 1. 只有一个结点
        ListNode *cur = head->next;
        if(cur == nullptr){
            return head;
        }

        // 2. 大于一个结点
        ListNode *prev = head;
        prev->next = nullptr;
        while(cur != nullptr){
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            if(next == nullptr){
                break;
            }
            cur = next;
        }
        head = cur;
        return head;
    }
};
void test01(){
}

int main(void){
    test01();
    return 0;
}