#include <iostream>
#include <vector>
#include <functional> // For std::less

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size);  
    void heapAdjust(size_t root, size_t size);
    void sort();
    void print();
private:
    std::vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size) : _vec(arr, arr + size) {}

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t root, size_t size)
{
    size_t leftChild = 2 * root + 1;
    size_t rightChild = 2 * root + 2;
    size_t max = root;

    if (leftChild < size && _cmp(_vec[max],_vec[leftChild]))
        max = leftChild;

    if (rightChild < size && _cmp(_vec[max],_vec[rightChild]))
        max = rightChild;

    if (max != root)
    {
        std::swap(_vec[root], _vec[max]);
        heapAdjust(max, size);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
    size_t size = _vec.size();

    // Build heap
    for (int i = size / 2 - 1; i >= 0; --i)
        heapAdjust(i, size);

    // Extract elements from heap
    for (int i = size - 1; i > 0; --i)
    {
        std::swap(_vec[0], _vec[i]);
        heapAdjust(0, i);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::print()
{
    for (const auto &elem : _vec)
        std::cout << elem << " ";
    std::cout << std::endl;
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    HeapSort<int> heapSort(arr, size);
    std::cout << "Original array: ";
    heapSort.print();

    heapSort.sort();

    std::cout << "Sorted array: ";
    heapSort.print();

    return 0;
}
