//=============================================================================
// if you have Y : X
// void f(Y*)
// void f(X*)
//
// X* x = new Y;
// f(x)
// which will it call?

#include <iostream>
#include <string>

class X {
public:
  virtual std::string get() {
    return "X";
  }
  virtual ~X() {}
  
};

class Y : public X {
public:
  virtual std::string get() {
    return "Y";
  }
  virtual ~Y() {}
};

void func(X* x)
{
  std::cout << "X" << std::endl;
  std::cout << x->get() << std::endl;
  
}

void func(Y* y)
{
  std::cout << "Y" << std::endl;
  std::cout << y->get() << std::endl;
}

int main()
{
  X* x = new Y;
  func(x);
  delete x;
  return 0;
}
