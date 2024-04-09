#include <iostream>
#include <string>
using namespace std;

class Person{
public:
    Person(string name, int age)
    :_name(name)
    ,_age(age)
    {
        //cout << "Person(string,int)" << endl;
    }
    void display(){
        cout << "name: " << _name << ", age: "<< _age;
    }

private:
    string _name;
    int _age;    
};

class Employee : public Person{
public:
    Employee(string name,int age,string department,double salary)
    :Person(name,age)
    ,_department(department)
    ,_salary(salary)
    {
        _sum += _salary;
        ++_count;
       //cout << "Employee(string,int,string,double)" << endl;
    }
    // static double getSumSalary(double salary){
    //     _sum += salary;
    //     ++_count;
    // }
    static double getAverSalary(double sum,int count){
        return sum / count;
    }
    void display(){
        Person::display();
        cout << ", department: " << _department << ", salary: " << _salary << endl;
    }
    double getSalary() const{
        return _salary;
    }
    static double getSum(){
        return _sum;
    }
    static double getCount(){
        return _count;
    }
private:
    string _department;
    double _salary;
    static double _sum;
    static int _count;
};
double Employee::_sum = 0;
int Employee::_count = 0;

void test01(){
    Employee e1("Brian",18,"Alpha",10000);
    e1.display();
    Employee e2("Ethan",22,"Bravo",15000);
    e2.display();
    Employee e3("Jason",25,"Cali",20000);
    e3.display();
    // Employee::getSumSalary(e1.getSalary());
    // Employee::getSumSalary(e2.getSalary());
    // Employee::getSumSalary(e3.getSalary());
    // double averSalary = Employee::getSum() / Employee::getCount();

    cout << "平均工资:" << Employee::getAverSalary(Employee::getSum(),Employee::getCount()) << endl;
}

int main(void){
    test01();
    return 0;
}