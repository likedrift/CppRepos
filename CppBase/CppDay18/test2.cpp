#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template <typename T, typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com);
    void quick(int left, int right, Compare &com);
    int partition(int left, int right, Compare &com);
    void print();

private:
    vector<T> _vec;
};

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
{
    for (int i = 0; i < size; i++)
    {
        _vec.push_back(arr[i]);
    }
    quick(0, _vec.size() - 1, com);
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com){
    if(left >= right){
        return;
    }

    // left < right
    int pivotIdx = partition(left,right,com);
    quick(left,pivotIdx - 1,com);
    quick(pivotIdx+1,right,com);

}

template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com){
    T pivot = _vec[right];
    int i = left - 1;
    for(int j = left; j < right; j++){
        if(com(_vec[j], pivot)){
            i++;
            swap(_vec[i],_vec[j]);
        }
    }
    swap(_vec[i + 1], _vec[right]);
    return i + 1;
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::print(){
    for(const auto & elem : _vec){
            cout << elem << " ";
    }
    cout << endl;
}

void test01()
{
    int arr[] = {5, 2, 8, 1, 9, 4, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "before sort:" << endl;
    for(auto & elem : arr){
        cout << elem << " ";
    }
    cout << endl;
    
    cout << "after sort:" << endl;
    MyQsort<int> mq(arr,size,less<int>());
    mq.print();
}

int main(void)
{
    test01();
    return 0;
}