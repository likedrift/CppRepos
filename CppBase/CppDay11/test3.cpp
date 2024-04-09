#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class TextQuery{
public:
    TextQuery(){
        _lines.reserve(107);
    }
    void readFile(const string filename);
    void query(const string & word);
    void preProcessLine(string & line);
    void dealLine(string & line);
private:
    // _lines存的是一行一行的内容
    // 查找到单词后需要输出该行的全部内容
    vector<string> _lines;
    // 单词和行号
    map<string,set<int>> _wordNumbers;
    // 单词和词频
    map<string,int> _dict;
};

void TextQuery::readFile(const string filename){
    ifstream ifs(filename);
    if(!ifs){
        cerr << "ifs open file failed." << endl;
        return;
    }
    string line;
    size_t lineNumber = 0;
    while(getline(ifs,line)){
        // 读一行，就把这行的内容不经任何处理保存到vector
        _lines.push_back(line);
        
        // 对读取的一行的内容进行处理
        dealLine(line);

        istringstream iss(line);
        string word;
        while(iss >> word){
            // 统计单词和词频
            ++_dict[word];
            // 记录单词和行号
            _wordNumbers[word].insert(lineNumber);
        }
        ++lineNumber;
    }
}

void TextQuery::dealLine(string & line){
    // 不应该直接舍弃掉字母之外的内容
    // 用空格替换所有非字母部分
    for(auto & ch : line){
        if(!isalpha(ch)){
            ch = ' ';
        }else if(isupper(ch)){
            ch = tolower(ch);
        }
    }
}

void TextQuery::query(const string & word){
    cout << "------------------" << endl;
    // 获取单词出现次数
    int count = _dict[word];
    // 输出单词+次数的形式
    cout << word << " occurs " << count << (count > 1? " times." : " time.") << endl;

    auto lines = _wordNumbers[word];
    for(auto & num : lines){
        cout << "(line " << num + 1 << ")" << _lines[num] << endl; 
    }

}
void test01(){
    string queryWord("this");
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
}

int main(void){
    test01();
    return 0;
}