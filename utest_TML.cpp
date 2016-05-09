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

// <nnn> //=============================================================================
// <nnn> TEST(If, int)
// <nnn> {
// <nnn>   TEST_EQUAL((If<true, 1, 2>::result), 1);
// <nnn>   TEST_EQUAL((If<false, 1, 2>::result), 2);
// <nnn> }

// <nnn> //=============================================================================
// <nnn> TEST(Sqrt, perfect)
// <nnn> {
// <nnn>   TEST_EQUAL(Sqrt<16>::result, 4u);
// <nnn> }

//=============================================================================
TEST(Less, test)
{
  TEST_TRUE((Less<2, 3>::result));
  TEST_FALSE((Less<2, 2>::result));
  TEST_FALSE((Less<8, 3>::result));
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
