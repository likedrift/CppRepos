#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size);
    void heapAdjust(size_t ,size_t);
    void sort();
    void print();
private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T * arr, size_t size)
:_vec(arr,arr + size){}

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t root, size_t size){

    // lchild
    size_t lchild = 2 * root + 1;
    // rchild
    size_t rchild = 2 * root + 2;
    // root
    size_t max = root;

    if(lchild < size && _cmp(_vec[max],_vec[lchild])){
        max = lchild;
    }

    if(rchild < size && _cmp(_vec[max],_vec[rchild])){
        max = rchild;
    }

    if(max != root){
        swap(_vec[root],_vec[max]);
        heapAdjust(max,size);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort(){
    size_t size = _vec.size();
    // 建堆
    for(int i = size / 2 - 1; i >= 0; --i){
        heapAdjust(i,size);
    }
    // 从堆中提取元素
    for(int i = size - 1; i > 0; --i){
        swap(_vec[0],_vec[i]);
        heapAdjust(0, i);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::print(){
    for(const auto & elem : _vec){
        cout << elem << " ";
    }
    cout << endl;
}
void test01(){
    int arr[] = {5, 1, 4, 10, 6, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    HeapSort<int> hs(arr,size);
    cout << "before sort:" << endl;
    hs.print();

    hs.sort();

    cout << "after sort:" << endl;
    hs.print();
}

int main(void){
    test01();
    return 0;
}