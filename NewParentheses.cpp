//=============================================================================
// From here:
// http://stackoverflow.com/questions/620137/do-the-parentheses-after-the-type-name-make-a-difference-with-new
//
// In g++ this works as (I) would expect. In cl, this works how the standard
// would suggest.

#include <assert.h>
#include <iostream>

//=============================================================================
struct A {
public:
  int member;
};
  
//=============================================================================
class B {
public:
  int member;
};

//=============================================================================
class C {
public:

  ~C() {} // = default not compiler supported.
  
  int member;
};


//=============================================================================
int main()
{
  std::cout << std::endl;

  A* a_1 = new A;
  A* a_2 = new A();
  std::cout << "member of a_1: " << a_1->member << std::endl;
  std::cout << "member of a_2: " << a_2->member << std::endl;
  std::cout << std::endl;

  B* b_1 = new B;
  B* b_2 = new B();
  std::cout << "member of b_1: " << b_1->member << std::endl;
  std::cout << "member of b_2: " << b_2->member << std::endl;
  std::cout << std::endl;

  C* c_1 = new C;
  C* c_2 = new C();
  std::cout << "member of c_1: " << c_1->member << std::endl;
  std::cout << "member of c_2: " << c_2->member << std::endl;
  std::cout << std::endl;

  delete a_1;
  delete a_2;
  delete b_1;
  delete b_2;
  delete c_1;
  delete c_2;

  return 0;
}
