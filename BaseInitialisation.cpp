//=============================================================================
//
// This shows that you shouldn't call virtual functions in a base constructor.

#include <iostream>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class Base {
public:
  Base()
    {
      set_a();
    }
  virtual void set_a()
    {
    }
      
private:
};

//=============================================================================
class Derived : public Base {
public:

  Derived()
    : Base(),
      m_a(0),
      m_a_set(false)
    {
    }
  
  virtual void set_a() override
    {
      m_a = 54;
      m_a_set = true;
    }

private:
  friend class utest_BaseInitialisation;
  int m_a;
  bool m_a_set;
};

//=============================================================================
class utest_BaseInitialisation : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_ctor();
  }

private:

  void test_ctor();

};

//=============================================================================
void utest_BaseInitialisation::test_ctor()
{
  print(DGC_CURRENT_FUNCTION);
  Derived d;
  test(!d.m_a_set, "a has not been set");
  

}

//=============================================================================
int main() {
  utest_BaseInitialisation test;
  test.run_tests();
  return 0;
}
