#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Student{
public:
    Student(int id,const char *name)
    :_id(id)
    ,_name(new char[strlen(name) + 1]())
    {
        strcpy(_name,name);
        cout << "Student(int, const char *)" << endl;
    }

    // 拷贝构造
    Student(const Student & rhs)
    :_id(rhs._id)
    ,_name(new char[strlen(rhs._name) + 1]())
    {
        strcpy(_name,rhs._name);
        cout << "Student(const Student &)" << endl;
    }

    // 赋值运算符函数
    Student & operator=(const Student & rhs){
        // 如果不是自复制才进入自定义赋值流程
        if(this != &rhs){
            // 1.回收原本的空间
            delete [] _name;
            // 2.深拷贝
            _name = new char[strlen(rhs._name)+1]();
            // 3.字符串拷贝
            strcpy(_name,rhs._name);
            // 其他内容
            _id = rhs._id;

            cout << "Student & operator=(const Student &)" << endl;
        }
        return *this;// 返回本对象
    }

    static void destroy(Student * pstu){
        if(pstu){
            delete pstu;
            pstu = nullptr;            
        }
    }

    void print(){
        cout << "(" << "id = " << _id << ",name = " << _name << ")" << endl;
    }


private:
        ~Student(){
        // 如果非空就清理
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
        cout << "~Student()" << endl;
    }
private:
    int _id;
    char *_name;
};


void test01(){
    Student * stu1 = new Student(1,"Jay");  
    stu1->print();
    Student::destroy(stu1);
}

int main(void){
    test01();
    return 0;
}