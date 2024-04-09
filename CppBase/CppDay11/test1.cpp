#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <time.h>
#include <algorithm>
using namespace std;

struct Record{
    Record(const string &word,int frequency)
    :_word(word)
    ,_frequency(frequency)
    {}
    string _word;
    int _frequency;

    // bool operator==(const Record & rhs){
    //     if(_word == rhs._word){
    //         return true;
    //     }
    //     return false;
    // }
};

class Dictionary{
public:
    Dictionary(int capacity){
        _dict.reserve(capacity);
    }
    void read(const string &filename);
    void store(const string &filename);
    bool isLegal(string & word){
        size_t size = word.size();
        for(int i = 0; i < size;++i){
            if(!isalpha(word[i])){
                return false;
            }
            word[i] = tolower(word[i]);
        }
        // for(char & c : word){
        //     if(!isalpha(c)){
        //         return false;
        //     }
        //     // 合法的全部转成小写
        //     if(isupper(c)){
        //         c = tolower(c);
        //     }
        // }
        return true;
    }
    void isExist(const string &word){
        for(auto & indiv : _dict){
            if(indiv._word == word){
                ++indiv._frequency;
                return;
            }
        }
        _dict.push_back(Record(word,1));
    }

private:
    vector<Record> _dict;
};

bool operator<(const Record & lhs, const Record & rhs){
    return lhs._word < rhs._word;
}

void Dictionary::read(const string &filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cout << "ifstream open file failed." << endl;
        return;
    }
    
    string word;
    // 因为磁盘读写速度慢，应该尽量减少读写次数
    // while(ifs >> word){
    //     if(isLegal(word)){// 处理单词
    //         isExist(word);// 将单词插入到vector
    //     }
    // }

    // 按行读取
    string line;
    while(getline(ifs,line)){
        istringstream iss(line);
        string word;
        while(iss >> word){// 直接在内存中进行，比磁盘快得多
            if(isLegal(word)){// 处理单词
                isExist(word);// 将单词插入到vector
            }
        }
    }
    sort(_dict.begin(),_dict.end());
    ifs.close();
}

void Dictionary::store(const string &filename){
    ofstream ofs(filename);

    for(auto & indiv : _dict){
        ofs << indiv._word << " " << indiv._frequency << endl;
    }

    ofs.close();
}

void test01(){
    Dictionary dict(10000);
    time_t begin = time(NULL);
    dict.read("The_Holy_Bible.txt");
    dict.store("dict1.txt");
    cout << "Total dealing time is " << time(NULL) - begin << " second" << endl;
}

int main(void){
    test01();
    return 0;
}