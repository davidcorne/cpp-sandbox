//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"

using namespace std;


//=============================================================================
template <class T>
class Ptr {
public:
  Ptr (T* ptr)
    : m_ptr(ptr)
    {
      assert(m_ptr);
    }
  
  Ptr (Ptr const & p)
    : m_ptr (p.m_ptr)
    {
      std::cout << "Copy constructor\n";
    }

  template <class U>
  Ptr (Ptr <U> const & p)
  // Supporting coercion using member template constructor.
  // This is not a copy constructor, but behaves similarly.
    : m_ptr (p.m_ptr) // Implicit conversion from U to T required
    {
      std::cout << "Coercing member template constructor\n";
    }
  
  // Copy assignment operator.
  Ptr & operator = (Ptr const & p)
    {
      m_ptr = p.m_ptr;
      std::cout << "Copy assignment operator\n";
      return *this;
    }
  
  template <class U>
  Ptr & operator = (Ptr <U> const & p)
  // Supporting coercion using member template assignment operator.
  // This is not the copy assignment operator, but works similarly.
    {
      m_ptr = p.m_ptr; // Implicit conversion from U to T required
      std::cout << "Coercing member template assignment operator\n";
      return *this;
    }
  
  T* m_ptr;
private:

  friend class utest_CoercionByMemberTemplate;
  
  // <nnn> template <class U>
  // <nnn> friend class Ptr<U>;
  
};

//=============================================================================
class Base {
};

//=============================================================================
class Derived : public Base {
};

//=============================================================================
class utest_CoercionByMemberTemplate : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_();
  }

private:

  void test_();

};

//=============================================================================
void utest_CoercionByMemberTemplate::test_()
{
  print(DGC_CURRENT_FUNCTION);
  Base base;
  Ptr<Base> p_base(&base);
  Derived derived;
  Ptr<Derived> p_derived(&derived);

  Ptr<Base> new_p_base = p_derived;
  test(new_p_base.m_ptr, "Non-null pointer.");
}

//=============================================================================
int main() {
  utest_CoercionByMemberTemplate test;
  test.run_tests();
  return 0;
}
