//=============================================================================

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
