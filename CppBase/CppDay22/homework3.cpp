#include <iostream>
#include <vector>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) 
    :_capacity(capacity)
    {
        cout << "LRUCache(int)" << endl;
    }
    
    int get(int key) {

    }
    
    void put(int key, int value) {

    }
private:
    int _capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */