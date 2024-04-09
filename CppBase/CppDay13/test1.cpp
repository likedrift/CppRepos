#include <iostream>
#include <string.h>
using namespace std;

class Person{
public:
    Person(const char * name, int age)
    :_name(new char[strlen(name) + 1]())
    ,_age(age)
    {
        strcpy(_name,name);
        // cout << "Person(char *,int)" << endl;
    }

    ~Person(){
        if(_name){
            delete [] _name;
            _name = nullptr;
            // cout << "~Person()" << endl;
        }
    }

    Person(const Person & rhs)
    :_name(new char[strlen(rhs._name) + 1]())
    ,_age(rhs._age)
    {
        strcpy(_name,rhs._name);
        // cout << "Person(const Person &)" << endl;
    }

    Person & operator=(const Person & rhs){
        if(this != &rhs){
            delete [] _name;
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name,rhs._name);
            // cout << "Person &operator=(const Person&)" << endl;
        }
        return *this;
    }

    void display(){
        cout << "name:" << _name << ",age:" << _age ;
    }
private:
    char * _name;
    int _age;
};

class Employee : public Person{
public:
    Employee(const char * name, int age,const char * department, int salary)
    :Person(name,age)
    ,_department(new char[strlen(department) + 1]())
    ,_salary(salary)
    {
        strcpy(_department,department);
        // cout << "Employee*(const char *, int, const char *, int)" << endl;
    }

    ~Employee(){
        if(_department){
            delete [] _department;
            _department = nullptr;
        }
        // cout << "~Employee()" << endl;
    }

    Employee(const Employee & rhs)
    :Person(rhs)
    ,_department(new char[strlen(rhs._department) + 1]())
    ,_salary(rhs._salary)
    {
        strcpy(_department,rhs._department);
        // cout << "Employee(const Employee &)" << endl;
    }

    Employee &operator=(const Employee & rhs){
        if(this != &rhs){
            Person::operator=(rhs);
            delete [] _department;
            _department = new char[strlen(rhs._department) + 1]();
            // cout << "Employee &operator=(const Employee &)" << endl;
            strcpy(_department,rhs._department);
        }
        return *this;
    }

    void display(){
        Person::display();
        cout << ",department:" << _department << ",salary:" << _salary << endl;
    }
private:
    char * _department;
    int _salary;
};
void test01(){
    Employee e1("Alex",18,"Alpha",10000);
    Employee e2("Ethan",20,"Bravo",15000);
    Employee e3("Brian",25,"Cali",20000);

    e1.display();
    e2.display();
    e3.display();
    Employee e4(e1);
    e3 = e2;
    e3.display();
    e4.display();
}

int main(void){
    test01();
    return 0;
}