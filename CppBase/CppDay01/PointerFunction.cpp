#include <iostream>

using std::cout;
using std::endl;

char *funcTest(char *words){
    char *getWords = words;
    return getWords;
}

int main(void){
    //PointerFunction
    //指针函数
    static char words[20] = "Hello,world!";
    cout << words << endl;
    char *getWords = funcTest(words);
    cout << getWords << endl;
    return 0;
}