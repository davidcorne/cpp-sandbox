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
TEST(Optional, default)
{
  Optional<int> opt_int;
  TEST_FALSE(opt_int, "Default constructed optional should be false.");
  Optional<NonDefault> opt_non_default;
  TEST_FALSE(opt_non_default, "Default constructed optional should be false.");
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
