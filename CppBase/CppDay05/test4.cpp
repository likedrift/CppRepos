#include <iostream>

using std::cout;
using std::endl;

const int defaultSize = 3;

class Stack{
public:
    Stack() = default;
    Stack(int size = defaultSize)
    :_arr(new int[size]())
    ,_index(-1)
    ,_size(size)
    {
        if(_size < defaultSize){
            exit(1);
        }
        cout << "Stack(int)" << endl;
    }
    ~Stack(){
        if(_arr){
            delete [] _arr;
            _arr = nullptr;
        }
        cout << "~Stack()" << endl;
    }
    bool empty(){
        return _index == -1;
    }
    bool full(){
        return (_index == _size - 1);
    }
    void push(int val){
        if(full()){
            cout << "Stack is full!" << endl;
            return;
        }
        _arr[++_index] = val;
    }
    void pop(){
        if(empty()){
            cout << "Stack is empty!" << endl;
            return;
        }
        _index--;
    }
    int top(){
        if(empty()){
            throw "Stack is empty!";
        }
        return _arr[_index];
    }

    void print(){
        for(int i = 0; i <= _index; i++){
            cout << _arr[i] << endl;
        }
    }

private:
    int *_arr;
    int _index;
    int _size;
};

void test01(){
    int size = 5;
    Stack s(size);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.print();
    if(s.full()){
        cout << "Stack is full!" << endl;
    }
    s.pop();
    s.pop();
    s.pop();
    s.print();
    s.pop();
    s.pop();
    if(s.empty()){
        cout << "Stack is empty!" << endl;
    }
    int topValue = 0;
    try{
        topValue = s.top();
    }catch(const char * msg){
        cout << "Exception:" << msg << endl;
    }
    //cout << topValue << endl;
}

int main(void){
    test01();
    return 0;
}