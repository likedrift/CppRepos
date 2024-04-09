#include <iostream>
#include <stdio.h>
class A
{
public:
 void FuncA()
 {
     printf( "FuncA called\n" );
 }
 virtual void FuncB()
 {
     printf( "FuncB called\n" );
 }
};

class B 
: public A
{
public:
 void FuncA()
 {
     A::FuncA();
     printf( "FuncAB called\n" );
 }
    
 virtual void FuncB()
 {
     printf( "FuncBB called\n" );
 }
};

int main( void )
{
	B b;
	A *pa;
	pa = &b; // 父类指针指向子类对象
	A *pa2 = new A; // 堆上开辟空间调用无参构造
	pa->FuncA(); // 
	pa->FuncB();
	pa2->FuncA();
	pa2->FuncB();
	delete pa2;
	

	return 0;

}