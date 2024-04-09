#include <iostream>
using std::cout;
using std::endl;

#include <math.h>

#include <string>
using std::string;

#include <memory>
using std::unique_ptr;


class Figure{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;
    virtual ~Figure(){}
};

class Rectangle : public Figure{
public:
    Rectangle(double length = 0, double width = 0)
    : _length(length)
    , _width(width)
    {}

    void display() const override {
        cout << "Rectangle:" << " length = " << _length << " width = " << _width;
    }

    double area() const override {
        return _length * _width;
    }

    ~Rectangle(){
        cout << "~Rectangle()" << endl;
    }

private:
    double _length;
    double _width;
};

class Circle : public Figure{
public:
    Circle(double radius = 0)
    :_radius(radius)
    {}

    void display() const override{
        cout << "Circle:" << " radius = " << _radius;
    }

    double area() const override{
        return 3.14 * _radius * _radius;
    }

    ~Circle(){
        cout << "~Circle()" << endl;
    }

private:
    double _radius;
};

class Triangle : public Figure{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    :_a(a)
    ,_b(b)
    ,_c(c)
    {}

    void display() const override{
        cout << "Triangle:" << " a = " << _a << " b = " << _b 
                            << " c = " << _c;
    }
    
    double area() const override{
        // 海伦公式
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};

void func(Figure *pfig){
    pfig->display();
    cout << " area = " << pfig->area() << endl;
}

class Factory{
public:
    virtual Figure *create() = 0;
    virtual ~Factory(){}
};

class RectangleFactory : public Factory{
public:
    virtual Figure *create() override{
        Rectangle *prec = new Rectangle(10 , 20);
        return prec;
    }
};

class CircleFactory : public Factory{
public:
    virtual Figure *create() override{
        Circle *pcir = new Circle(5);
        return pcir;
    }
};

class TriangleFactory : public Factory{
public:
    virtual Figure *create() override{
        Triangle *ptri = new Triangle(3,4,5);
        return ptri;
    }
};

void test01(){
    // Rectangle工厂生产商品
    // new RectangleFaactory()生产出的商品用recFac先暂存
    unique_ptr<Factory> recFac(new RectangleFactory());
    // 因为创建的是Rectangle，决定实例化这个商品
    unique_ptr<Figure> recFig(recFac->create());
    // 获取裸指针
    func(recFig.get());

    unique_ptr<Factory> triFac(new TriangleFactory());
    unique_ptr<Figure> triFig(triFac->create());
    func(triFig.get());

}

int main(void){
    test01();
    return 0;
}