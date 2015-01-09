//=============================================================================
//
// This is from:
// http://stackoverflow.com/questions/27828822/cant-understand-this-way-to-calculate-the-square-of-a-number
//
// Note this is undefined behaviour, so it won't work on some compilers.

#include <UnitCpp/Test.h>

#include "Compiler.h"

#if COMPILER_TYPE != COMPILER_TYPE_VS

//=============================================================================
int square(int n) {
  int a[n]; //works on C99 and above
  return (&a)[n] - a;
}

//=============================================================================
TEST(ObfuscatedSquare, square)
{
  TEST_EQUAL(square(2), 4);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN("Cannot allocate an array of constant size");
#endif

