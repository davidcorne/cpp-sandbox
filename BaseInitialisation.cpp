//=============================================================================
//
// This shows that you shouldn't call virtual functions in a base constructor.

#include <iostream>

#include <UnitCpp.h>

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
  UNITCPP_FRIEND_TEST(BaseInitialisation, constructor);
  int m_a;
  bool m_a_set;
};


//=============================================================================
TEST(BaseInitialisation, constructor)
{
  Derived d;
  TEST_FALSE(d.m_a_set, "a has not been set");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
