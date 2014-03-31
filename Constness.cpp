//=============================================================================
//
// Found an unusual bug and tested it here. If you have a reference (or a
// pointer) as a member of your class, in a const function you can call
// non-const functions on the member. This is because it doesn't change the
// reference (or pointer) which the class keeps, what it does is change is the
// object it references.

#include <iostream>

//=============================================================================
class Bar {
public:

  Bar()
    : m_num(5)
    {
    }
  
  void non_const() {
    m_num += 10;
    std::cout << m_num << std::endl;
  }
private:

  int m_num;

};

//=============================================================================
class Foo {
public:

  Foo(Bar& bar)
    : m_bar(bar)
    {
    }
  
  void method() const {
    m_bar.non_const();
  }
  
private:

  Bar& m_bar;

};
  

//=============================================================================
int main()
//
//D 
//
{
  Bar bar;
  Foo foo(bar);
  foo.method();
  foo.method();
  return 0;
}
