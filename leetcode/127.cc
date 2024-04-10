#include <iostream>
#include <list>
#include <utility>
#include <unordered_map>
using namespace std;

class LRUCache{
public:
    LRUCache(int capacity)
    :_capacity(capacity)
    {

    }

    // 获取list中key对应的value
    int get(int key){
        // 和put一样，在map中查找key值是否存在
        auto it = _cache.find(key);
        if(it != _cache.end()){
            // 找到了 更新为list最新使用的key-value
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            return it->second->second;
        }else{ // 没找到 返回-1
            return -1;
        }
    }

    void put(int key, int value){
        // 在_cache中查找list中的key是否存在
        // 如果存在则返回对应位置的迭代器
        // unordered_map<int,list::iterator>::iterator
        auto it = _cache.find(key);
        // 找到则不会返回尾后迭代器
        if(it != _cache.end()){
            // 1.更新value
                it->second->second = value;
            // 2.更新关键字使用为最新状态
            // 把list中这个key-value放到list的开头位置
            // splice(元素要插入的位置,待操作列表,要被移动的元素的位置)
            _nodes.splice(_nodes.begin(), _nodes, it->second);
        }else{ // key不在链表中
            // 如果list已满 仍要插入元素 就要逐出最久未使用的关键字
            // 而在list中 最久未使用的关键字就是 链表最后位置的元素
            if(_capacity == (int)_nodes.size()){
                // 1. 先获取list的最后一个元素
                auto & deleteNode = _nodes.back();
                // 2. 删除最后一个元素
                // 这里应该先erase再pop_back
                /*
                    如果先执行 pop_back()，会导致最后一个元素被移除
                    因此 _nodes 中就不再包含那个元素，那个元素的迭代器也就无效了
                    如果在此时尝试使用无效的迭代器执行 _cache 的 find() 操作
                    将无法找到对应的元素，因为已经从 _cache 中移除了相应的键值对
                */
                _cache.erase(_cache.find(deleteNode.first));
                _nodes.pop_back();
            }

            // 将key-value插入到list的最前面
            _nodes.push_front(pair<int, int>(key, value));
            // 更新unordered_map
            _cache[key] = _nodes.begin();
        }
    }

    void print() const{
        for(auto & elem : _nodes){
            cout << elem.first << "-" << elem.second << " ";
        }
        cout << endl;
    }

private:
    int _capacity; // 元素个数
    list<pair<int, int>> _nodes; // 存放元素的节点
    // 用于快速查找缓存中特定键的位置，将键映射到_nodes中对应键值对的迭代器
    // 以便在缓存命中时能够快速定位和更新缓存
    unordered_map<int, list<pair<int, int>>::iterator> _cache;
};

void test01(){
    LRUCache cache(3);
    cache.put(1,100);
    cache.print();

    cache.put(2,200);
    cache.print();

    cache.put(3,300);
    cache.print();

    cache.put(4,400);
    cache.print();

    cout << "get(2)" << cache.get(2) << endl;
    cache.print();

    cout << "get(3)" << cache.get(3) << endl;
    cache.print();
}

int main(void){
    test01();
    return 0;
}