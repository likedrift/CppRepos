#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::unordered_map;
using std::istringstream;

class WordsReplace{
public:
    void readFile(const string & filename);
    void readMap(const string & filename);
    void replace(string & word);
    
private:
    unordered_map<string,string> _map;
    vector<string> _file;
};

void WordsReplace::readMap(const string & filename){
    ifstream ifs(filename);
    if(!ifs){
        cout << "ifstream open file failed." << endl;
        return;
    }

    string line;
    // 按行读取
    while(getline(ifs,line)){
        istringstream iss(line);
        // string word;
        string wordFirst = "";
        string wordSecond = "";

        // 插入第一个位置
        iss >> wordFirst;
        // 插入第二个位置
        getline(iss, wordSecond);
        // wordSecond += word;
        // wordSecond += " ";
        // _map.insert({wordFirst,wordSecond});
        
        // 去除wordSecond开头的空格
        if(!wordSecond.empty() && wordSecond[0] == ' '){
            wordSecond.erase(0,1);
        }
        _map[wordFirst] = wordSecond;
    }
}

void WordsReplace::readFile(const string & filename){
    ifstream ifs(filename);
    if(!ifs){
        cout << "ifstream open file failed." << endl;
        return;
    }
    string line;
    while(getline(ifs,line)){
        istringstream iss(line);
        string word;
        string newLine;
        while(iss >> word){
            replace(word);
            newLine += word + " ";
        }
        _file.push_back(newLine);
    }
    ifs.close();

    ofstream ofs(filename);
    for(const auto & elem : _file){
        ofs << elem << endl;
    }
    ofs.close();
}

void WordsReplace::replace(string & word){
    auto it = _map.find(word);
    if(it != _map.end()){
        word = it->second;
    }
}

void test01(){
    WordsReplace wr;
    wr.readMap("map.txt");
    wr.readFile("file.txt");
}

int main(void){
    test01();
    return 0;
}