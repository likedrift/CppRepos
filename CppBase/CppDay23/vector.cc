#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::allocator;

template<typename T> 
class Vector 
{ 
public:
    // 需要在自定义的类中显式给出begin迭代器和end迭代器的实现
    // 否则增强for循环无法使用，因为编译器不知道如何迭代自定义类对象
    using iterator = T *; // 给T*取别名 这样做的目的是为了提供一种简便的方法来定义迭代器类型，以便在类的其他地方使用。

    iterator begin(){
        return _start;
    }

    iterator end(){
        return _finish;
    }

    Vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_end_of_storage(nullptr)
    {

    }
    ~Vector();          
    void push_back(const T &);      
    void pop_back();         
    int size() const;     
    int capacity() const; 
private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};

// 初始化Vector中的静态成员变量
template<typename T>
std::allocator<T> Vector<T>:: _alloc;

template<typename T>
Vector<T>::~Vector(){
    // 不为空就清理
    if(_start){
        while(_start != _finish){
            // 用--finish而不是start++原因在于后面的deallocate要用start，此时start已经偏移了
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,capacity());
    }
}

template<typename T>
void Vector<T>::push_back(const T &value){
    // 插入元素，如果满了就扩容
    if(size() == capacity()){
        reallocate();
    }

    // 没满就构造对象
    if(size() < capacity()){
        _alloc.construct(_finish++,value);
    }
}

template<typename T>
void Vector<T>::pop_back(){
    // 不为空就执行删除元素
    if(size() > 0){
        _alloc.destroy(--_finish);
    }
}

template<typename T>
int Vector<T>::size() const{
    return _finish - _start;
}

template<typename T>
int Vector<T>::capacity() const{
    return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::reallocate(){
    // 1.开辟新的空间
    int oldCapacity = capacity();
    int newCapacity = capacity() > 0 ? 2 * capacity() : 1;
    T *newTemp = _alloc.allocate(newCapacity);

    if(_start){
        // 2.使用原本空间的内容初始化新的空间
        std::uninitialized_copy(_start,_finish,newTemp);
        // 3.回收原本的空间
        while(_start != _finish){
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,oldCapacity);
    }

    // 在新的空间中关联vector的三个指针
    _start = newTemp;
    _finish = newTemp + oldCapacity;
    _end_of_storage = newTemp + newCapacity;

}

template<typename T>
void printSizeAndCapacity(const Vector<T> &container){
    cout << "size = " << container.size() << ", capacity = " << container.capacity() << endl;
}

template<typename T>
void printVector(Vector<T> &vec){// 形参中 Vector前面不要加const，因为在Vector的begin()和end()没有使用const
// ↑ 可以选择在begin()和end()处加const，也可以在形参中去掉const
    
    // 增强for循环遍历自定义的Vector
    for(auto & elem : vec){
        cout << elem << " ";
    }
    cout << endl;
}
void test01(){
    Vector<int> vec;
    vec.push_back(1);
    printVector<int>(vec);
    printSizeAndCapacity<int>(vec);

    vec.push_back(2);
    printVector<int>(vec);
    printSizeAndCapacity<int>(vec);

    vec.push_back(3);
    printVector<int>(vec);
    printSizeAndCapacity<int>(vec);

    vec.push_back(4);
    printVector<int>(vec);
    printSizeAndCapacity<int>(vec);

    vec.push_back(5);
    printVector<int>(vec);
    printSizeAndCapacity<int>(vec);
}

int main(void){
    test01();
    return 0;
}