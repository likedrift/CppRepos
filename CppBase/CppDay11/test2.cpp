#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <time.h>
using namespace std;

// struct Record{
//     string _word;
//     int _frequency;
// };

class Dictionary{
public:
    void read(const string &filename);
    void store(const string &filename);
    bool isLegal(string word){
    for(char c : word){
        if(!isalpha(c)){
            return false;
        }
    }
    return true;
    }
private:
    map<string,int> _dict;
};

void Dictionary::read(const string &filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cout << "ifstream open file failed." << endl;
        return;
    }

    string word;
    while(ifs >> word){
        if(isLegal(word)){
            //++_dict[word];
            //存在则frequency+1，不存在则插入一个新的pair，string为新单词，并让frequency+1，其中frequency默认为0
            auto ret = _dict.insert({word,1});
            if(!ret.second){
                ++((*(ret.first)).second);
            }
        }
    }
}

void Dictionary::store(const string &filename){
    ofstream ofs(filename);
    for(auto & indiv : _dict){
        ofs << indiv.first << " " << indiv.second << endl;
    }
}

void test01(){
    Dictionary dict;
    time_t begin = time(NULL);
    dict.read("The_Holy_Bible.txt");
    dict.store("dict2.txt");
    cout << "Total dealing time is " << time(NULL) - begin << " second" << endl;
}

int main(void){
    test01();
    return 0;
}