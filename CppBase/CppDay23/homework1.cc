#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isValid(string s){
        vector<char> vec;
        for (int i = 0; i < s.size(); ++i){
            // ()
            switch (s[i]){
            case '(':
            case '{':
            case '[':
                vec.push_back(s[i]);
                continue;
            case ')':
                if (!vec.empty() && vec.back() == '('){
                    vec.pop_back();
                    continue;
                }else{
                    return false;
                }
            case '}':
                if (!vec.empty() && vec.back() == '{'){
                    vec.pop_back();
                    continue;
                }else{
                    return false;
                }
            case ']':
                if (!vec.empty() && vec.back() == '['){
                    vec.pop_back();
                    continue;
                }else{
                    return false;
                }
            }
        }
        if (vec.empty())
        {
            return true;
        }
        return false;
    }
};