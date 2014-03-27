//=============================================================================
//
// Monostate design pattern. A bit better singleton (possibly?)
// See http://c2.com/cgi/wiki?MonostatePattern for a little more detail.

#include <iostream>

#include "UnitTest.h"

using namespace std;

//=============================================================================
template <class T>
class InitialiseSafeStatic {
public:

  InitialiseSafeStatic()
    : m_initialised(false),
      m_value()
    {}
  
  void set_value(T value)
    {
      m_initialised = true;
      m_value = value;
    }

  bool initialised() const
    {
      return m_initialised;
    }
  
  T value() const
    {
      assert(initialised());
      return m_value;
    }
  
private:
  bool m_initialised;
  T m_value;  
};

//=============================================================================
class MonoState {
public:

  MonoState()
    {
      if (!m_value.initialised()) {
        m_value.set_value(1);
      }
    }

  void triple()
    {
      m_value.set_value(3 * m_value.value());
    }

  double value() const
    {
      return m_value.value();
    }
  
private:

  static InitialiseSafeStatic<double> m_value;
  friend class utest_MonoState;
};


//=============================================================================
class utest_MonoState : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_();
  }

private:

  void test_();

};

//=============================================================================
void utest_MonoState::test_()
{
  print(DGC_CURRENT_FUNCTION);
  MonoState m1;
  test(m1.value() == 1, "Incorrect starting value.");
  MonoState m2;
  test(m2.value() == 1, "Incorrect starting value.");
  m1.triple();
  test(m1.value() == 3, "Does not share state.");
  test(m2.value() == 3, "Does not share state.");
  test(&m1 != &m2, "Should not share memory.");
  
}

//=============================================================================
int main() {
  utest_MonoState test;
  test.run_tests();
  return 0;
}

// initialise static
InitialiseSafeStatic<double> MonoState::m_value;
