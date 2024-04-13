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
// 虚拟头结点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head; // 虚拟头结点的next指针指向真正的头结点
        ListNode *temp = dummyHead;

        while(temp->next && temp->next->next){
            ListNode *first = temp->next;
            ListNode *second = temp->next->next;
            
             // 1.更新头结点 其实也就是dummyHead->next = second
             // 2.后续会作为新的两两交换节点的前驱节点，next指向交换前第二个位置的节点
            temp->next = second;
            
            // 交换
            first->next = second->next;
            second->next = first;

            temp = first; // 交换后的first在第二位置，此时temp作为前驱存在
            
        }

    }
};