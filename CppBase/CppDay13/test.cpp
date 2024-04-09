#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class A {
  public:
    A( )
        : _pa(new int(11)){ };
    ~A( ) {
        delete _pa;
    }

  private:
    int *_pa;
};

class B {
  public:
    B( )
        : _pb(new int(22)){ };

    ~B( ) {
        delete _pb;
    }

  private:
    int *_pb;
};


class C : public A, public B {
  public:
    C( )
        : A( )
        , B( )
        , _c(new int(33)) {}

    ~C( ) {
        delete _c;
    }

  private:
    int *_c;
};


int main(void) {
    C *c1 = new C( );
    delete c1;

    return 0;
}