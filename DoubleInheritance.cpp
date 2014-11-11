//=============================================================================
//

#include "Capabilities.h"
#if CAPABILITY_DEFAULTED_FUNCTIONS
#include <iostream>

//=============================================================================
class A {
public:

  A();

  virtual ~A() = 0;
  
  virtual void run() = 0;

};

A::A() = default;
A::~A() = default;

//=============================================================================
class B {
public:

  B();

  virtual ~B() = 0;
  
  virtual void run() = 0;

};

B::B() = default;
B::~B() = default;

//=============================================================================
class C : public A, public B{
public:

  C();

  virtual ~C();
  
  virtual void run() override;

};

C::C() = default;
C::~C() = default;

//=============================================================================
void C::run()
{
  std::cout << "Running" << std::endl;
}

//=============================================================================
int main() {
  C* c = new C;
  
  A* a = c;
  a->run();
  
  B* b = c;
  b->run();

  delete c;
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif

