#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class Student
{
public:
    Student(int id,const char *name,int age)
    : _id(id)
    , _name(new char[strlen(name) + 1]())
    , _age(age)
    {
        strcpy(_name,name);
    }

    ~Student(){
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }
    void setId(int id);
    void setName(const char *name);
    void setAge(int age);
    void print();

    // 拷贝构造
    Student(const Student & rhs)
    : _id(rhs._id)
    , _name(new char[strlen(rhs._name) + 1]())
    , _age(rhs._age)
    {
        strcpy(_name,rhs._name);
    }

private:
    int _id;
    char *_name;
    int _age;
};

void Student::setId(int id)
{
    _id = id;
}

void Student::setName(const char *name)
{
    strcpy(_name, name);
}

void Student::setAge(int age)
{
    _age = age;
}

void Student::print()
{
    cout << "id = " << _id << ",name = " << _name << ",age = " << _age << endl;
}

int main(void)
{
    cout << "------ stu1 ------" << endl;
    Student stu1(0,"Tom",10);
    stu1.print();
    stu1.setId(1);
    stu1.setName("Jerry");
    stu1.setAge(18);
    stu1.print();
    cout << "------ stu2 ------" << endl;
    Student stu2(stu1);
    cout << "------ origin copy from stu1 ------" << endl;
    stu2.print();
    cout << "------ after set args ------" << endl;
    stu2.setAge(20);
    stu2.setId(2);
    stu2.setName("Alex");
    stu2.print();
    return 0;
}