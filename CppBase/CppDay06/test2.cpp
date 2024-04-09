    #include <iostream>
    #include <string>
    using std::cout;
    using std::endl;
    using std::cin;

    void test01(){
        std::string str;
        cin >> str;
        cout << str;
    }

    void test02(){
        char a[200] = {0};
        cin.getline(a,200,' ');
        cout << a;
    }
    int main(void){
        test01();
        return 0;
    }