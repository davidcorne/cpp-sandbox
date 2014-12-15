//=============================================================================
// Unit tests for GCD.h

#include "Capabilities.h"
#if CAPABILITY_CONSTEXPR
#include <UnitCpp/Test.h>

#include "GCD.h"
#include "GCD.h" // test multiple includes

//=============================================================================
TEST(MetaFractions, random_tests)
{
  TEST_EQUAL((GCD<16, 20>::result), 4);
  TEST_EQUAL((GCD<54, 24>::result), 6);
}

//=============================================================================
TEST(MetaFractions, gcd_base)
{
  TEST_EQUAL((GCD<0, 0>::result), 0);
  TEST_EQUAL((GCD<1, 0>::result), 1);
  TEST_EQUAL((GCD<2, 0>::result), 2);
  TEST_EQUAL((GCD<5, 0>::result), 5);
  TEST_EQUAL((GCD<10, 0>::result), 10);
  TEST_EQUAL((GCD<15, 0>::result), 15);
  TEST_EQUAL((GCD<20, 0>::result), 20);
  TEST_EQUAL((GCD<100, 0>::result), 100);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif

