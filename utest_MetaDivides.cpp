//=============================================================================
// Unit test for Divides

#include <UnitCpp/Test.h>

#include "Capabilities.h"
#if CAPABILITY_CONSTEXPR

#include "MetaDivides.h"
#include "MetaDivides.h" // test multiple includes

//=============================================================================
TEST(MetaDivides, divides)
{
  TEST_FALSE((Divides<4, 2>::result));
  TEST_TRUE((Divides<2, 4>::result));

  TEST_TRUE((Divides<1, 5>::result));
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
