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

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next){
            return head; // 链表为空或者只有一个节点，则无需交换，直接返回
        }

        ListNode *newHead = head->next; // 记录最后要返回的新的链表头结点，也就是原先链表的第二个节点
        ListNode *prev = nullptr; // 一开始前驱为空，这是用来连接每更新的两两节点之间的

        // 开始遍历链表 两两交换节点
        while(head && head->next){
            ListNode *first = head;
            ListNode *second = head->next;

            if(prev){ // 如果前面有节点了，就要更新前面节点连接的是后面的第二个节点
                prev->next = second;
            }
            
            // 两两结点交换
            first->next = second->next;
            second->next = first;

    
            prev = first; // 交换后的first原先第二个节点的位置，就作为下一轮两两交换的前驱节点
            head = first->next; // 更新当前节点位置，以进行下一次循环
        }
        return newHead;
    }
};

// class Solution {
// public:
//     ListNode* swapPairs(ListNode* head) {
//         if(head == nullptr){
//             return head;
//         }
//         ListNode *prev = head;
//         ListNode *curr = head->next;

//         bool isHead = true;
//         ListNode *newHead = head;

//         while(curr){

//             ListNode *temp = curr;
//             ListNode *nextFirst = temp->next;
//             ListNode *nextSecond = nullptr;
//             if(nextFirst != nullptr){
//                 ListNode *nextSecond = temp->next->next;
//             }


//             // ListNode *temp = nextFirst;
//             prev->next = curr->next;
//             curr->next = prev;

//             // 保持第一次交换后 head固定
//             if(isHead){
//                 isHead = false;
//                 newHead = curr;
//             }

//             // 恢复prev和curr的相对位置
//             prev = curr;
//             curr = temp;
        
//             if(nextSecond == nullptr){
//                 break;
//             }
//             curr->next = nextSecond;

//             prev = nextFirst;
//             curr = nextSecond;
//         }
//         return newHead;
//     }
// };

void test01(){

}

int main(void){
    test01();
    return 0;
}