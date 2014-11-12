//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_DELEGATING_CONSTRUCTOR

#include <iostream>

#include <UnitCpp/Test.h>

#include "Range.h"

//=============================================================================
TEST(Range, range_based_for)
{
  float check = -5.5;
  for (float f: Range<float>(-5.0, 10.0, 0.5)) {
    check += 0.5;
    TEST_EQUAL(f, check, "Wrong value for ", f, " expecting ", check, ".");
  }
  TEST_EQUAL(check, 9.5, "Wrong limit. Expecting 9.5, got ", check, ".");
}

//=============================================================================
TEST(Range, STL_style_for)
{
  Range<int> range(5);
  int i = -1;
  for (auto it = std::begin(range); it != std::end(range); ++it) {
    ++i;
    TEST_EQUAL(i, (*it), "Wrong value for ", i);
  }
  TEST_EQUAL(i, 4, "Wrong limit.");
}

//=============================================================================
TEST(Range, int)
{
  Range<int> range(5);

  TEST_TRUE(range, "Range should be good");
  TEST_EQUAL(range(), 0, "first element should be 0");
  ++range;
  
  TEST_TRUE(range, "Range should be good");
  TEST_EQUAL(range(), 1, "first element should be 1");
  ++range;
  
  TEST_TRUE(range, "Range should be good");
  TEST_EQUAL(range(), 2, "first element should be 2");
  ++range;
  
  TEST_TRUE(range, "Range should be good");
  TEST_EQUAL(range(), 3, "first element should be 3");
  ++range;
  
  TEST_TRUE(range, "Range should be good");
  TEST_EQUAL(range(), 4, "first element should be 4");
  ++range;

  TEST_FALSE(range, "Range should not be good");
}

//=============================================================================
TEST(Range, step)
{
  Range<double> range(0, 5, 0.5);
  for (double d = 0; d < 5; d += 0.5) {
    TEST_EQUAL(range(), d, "Range at ", d, " is wrong.");
    TEST_TRUE(range, "Range at ", d, " should be good.");
    ++range;
  }
  TEST_FALSE(range, "Range should be bad.");
}

//=============================================================================
TEST(Range, for)
{
  // This is the example use of Range<T>
  int i = -1;
  for (Range<int> range(5); range; ++range) {
    ++i;
    TEST_EQUAL(range(), i, "Wrong value for ", i, "th.");
  }
  TEST_EQUAL(i, 4, "Wrong limit for i.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_DELEGATING_CONSTRUCTOR)
#endif

