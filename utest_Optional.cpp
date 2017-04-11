//=============================================================================
//
// 

#include "Optional.h"

#include <UnitCpp.h>

//=============================================================================
class NonDefault {
public:

  NonDefault(int i) : m_i(i) {}
  int m_i;
};

//=============================================================================
class Destructor {
public:
  Destructor(bool* destructor_called) : m_destructor_called(destructor_called) {}

  ~Destructor() { (*m_destructor_called) = true;}

private:

  bool* m_destructor_called;
};

//=============================================================================
TEST(Optional, default)
{
  Optional<int> opt_int;
  TEST_FALSE(opt_int, "Default constructed optional should be false.");
  Optional<NonDefault> opt_non_default;
  TEST_FALSE(opt_non_default, "Default constructed optional should be false.");
}

//=============================================================================
TEST(Optional, destructor)
{
  bool destructor_called = false;
  {
    Destructor destructor(&destructor_called);
    Optional<Destructor> des(destructor);
  }
  TEST_TRUE(destructor_called, "The destructor should be called.");
  
}

//=============================================================================
TEST(Optional, non_default)
{
  Optional<int> opt_int(5);
  TEST_TRUE(opt_int, "Constructed optional should be true.");
  NonDefault nd(17);
  Optional<NonDefault> opt_non_default(nd);
  TEST_TRUE(opt_int, "Constructed optional should be true.");

  NonDefault new_nd = opt_non_default.value();
  TEST_EQUAL(new_nd.m_i, 17);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
