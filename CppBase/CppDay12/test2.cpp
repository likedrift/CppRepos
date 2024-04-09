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

class Cylinder : public Circle{
public:
    Cylinder(double r, double h)
    :Circle(r)
    ,_height(h)
    {
        cout << "Cylinder(double, double)" << endl;
    }
    double getVolume();
    void showVolume();

private:
    //Circle _circle;
    double _height;
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

double Cylinder::getVolume(){
    return getArea() * _height;
}

void Cylinder::showVolume(){
    cout << "Volume of cylinder = " << getVolume() << endl;
}
void test01(){
    Cylinder c(2,4);
    c.show();
    c.showVolume();
}

int main(void){
    test01();
    return 0;
}