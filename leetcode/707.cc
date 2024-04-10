#include <iostream>

using std::cout;
using std::endl;

struct LinkedNode{
    int val;
    LinkedNode *next;
    LinkedNode(int val)
    :val(val)
    ,next(nullptr)
    {

    }
};

class MyLinkedList {
public:
    MyLinkedList() 
    :_size(0)
    ,_dummyHead(new LinkedNode(0))
    {
        
    }
    
    int get(int index) {
        if(index > (_size -1 ) || index < 0){
            return -1;
        }

        LinkedNode *cur = _dummyHead->next;
        for(int i = 0; i < index; ++i){
            cur = cur->next;   
        }
        return cur->val;
    }

    void addAtHead(int val){
        LinkedNode *newNode = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;

        /*         if (_dummyHead->next == nullptr){
                    _dummyHead->next = newNode;
                    // 这里没有return就出问题了
                    // 因为上面的操作会导致下面的if语句为true
                    // _dummyHead->next就一直指向了自己
                    // 进而导致在addAtTail中，while循环无法退出，因为tmp->next一直指向自己
                    // 永远不会是nullptr
                }

                if (_dummyHead->next != nullptr){
                    newNode->next = _dummyHead->next;
                    _dummyHead->next = newNode;
                    _size++;
                }
         */
    }

    void addAtTail(int val) {
        LinkedNode *newNode = new LinkedNode(val);
        LinkedNode *tmp = _dummyHead;
        while(tmp->next != nullptr){
            // cout << "1" << endl;
            tmp = tmp->next;
        }
        // newNode->next = tmp->next;
        tmp->next = newNode;
        _size++;
    }
    
    void addAtIndex(int index, int val) {
        LinkedNode *newNode = new LinkedNode(val);

        if(index > _size || index < 0){
            return;
        }

        LinkedNode *prev = _dummyHead;
        // LinkedNode *cur = _dummyHead->next; 

        for(int i = 0; i < index; ++i){
            prev = prev->next;
            // cur = cur->next;
        }

        // 插入结点
        newNode->next = prev->next;
        prev->next = newNode;
        _size++;
    }
    
    void deleteAtIndex(int index) {
        if(index > (_size - 1) || index < 0){
            return;
        }

        // 走到这说明链表内一定有元素可以删除
        LinkedNode *prev = _dummyHead;
        for(int i = 0; i < index; ++i){
            prev = prev->next;
        }
        LinkedNode *tmp = prev->next;
        prev->next = prev->next->next;
        delete tmp;
        _size--;
    }

private:
    int _size;
    LinkedNode *_dummyHead;
};

void printLinkedList(MyLinkedList *myLinkedList){
    int idx = 0;
    while(1){
        int ret = myLinkedList->get(idx);
        if(ret == -1){
            break;
        }
        idx++;
        cout << ret << " ";
    }
    cout << endl;
}

int main(){
    // 6 1 2 0 4
    MyLinkedList *myLinkedList = new MyLinkedList();
    myLinkedList->addAtHead(7);// 7
    printLinkedList(myLinkedList);
    myLinkedList->addAtHead(2);// 2 7
    printLinkedList(myLinkedList);
    myLinkedList->addAtHead(1);// 1 2 7
    printLinkedList(myLinkedList);
    myLinkedList->addAtIndex(3,0);// 1 2 7 0
    printLinkedList(myLinkedList);
    myLinkedList->deleteAtIndex(2);// 1 2 0
    printLinkedList(myLinkedList);
    myLinkedList->addAtHead(6); // 6 1 2 0
    printLinkedList(myLinkedList);
    myLinkedList->addAtTail(4); // 6 1 2 0 4
    printLinkedList(myLinkedList);
    int ret = myLinkedList->get(4); // 4
    cout << ret << endl;
    printLinkedList(myLinkedList);
    myLinkedList->addAtHead(4);
    printLinkedList(myLinkedList);
    myLinkedList->addAtIndex(5,0);
    printLinkedList(myLinkedList);
    myLinkedList->deleteAtIndex(6);
    printLinkedList(myLinkedList);


}

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */