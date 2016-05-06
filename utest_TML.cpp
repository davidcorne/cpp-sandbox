//=============================================================================

#include <UnitCpp.h>

#include "Capabilities.h"
#ifdef CAPABILITY_CONSTEXPR

#include "TML.h"

//=============================================================================
TEST(If, bool)
{
  TEST_TRUE((If<true, true, false>::result));
  TEST_FALSE((If<false, true, false>::result));
}

//=============================================================================
TEST(If, int)
{
  TEST_EQUAL((If<true, 1, 2>::result), 1);
  TEST_EQUAL((If<false, 1, 2>::result), 2);
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
