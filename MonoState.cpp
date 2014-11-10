//=============================================================================
//
// Monostate design pattern. A bit better singleton (possibly?)
// See http://c2.com/cgi/wiki?MonostatePattern for a little more detail.

#include <assert.h>
#include <iostream>

#include <UnitCpp/Test.h>

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
TEST(MonoState, state)
{
  MonoState m1;
  TEST_EQUAL(m1.value(), 1, "Incorrect starting value.");
  MonoState m2;
  TEST_EQUAL(m2.value(), 1, "Incorrect starting value.");
  m1.triple();
  TEST_EQUAL(m1.value(), 3, "Does not share state.");
  TEST_EQUAL(m2.value(), 3, "Does not share state.");
  TEST_NOT_EQUAL(&m1, &m2, "Should not share memory.");
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

// initialise static
InitialiseSafeStatic<double> MonoState::m_value;
