#include <iostream>

using std::cout;
using std::endl;

class Circle{
public:
    Circle()
    :_radius(0)
    {
        cout << "Circle()" << endl;
    }

    Circle(double r)
    :_radius(r)
    {
        cout << "Circle(double)" << endl;
    }
    double getArea();
    double getPerimeter();
    void show();
private:
    double _radius;
};

double Circle::getArea(){
    return _radius * _radius * 3.14;
}

double Circle::getPerimeter(){
    return 2 * _radius * 3.14;
}

void Circle::show(){
    cout << "radius = " << _radius << ",Area = " << getArea() << ",Perimeter = " << getPerimeter() << endl;
}
void test01(){
    Circle c(2);
    c.show();
}

int main(void){
    test01();
    return 0;
}