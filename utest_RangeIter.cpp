//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_DELEGATING_CONSTRUCTOR
#include <iostream>
#include <UnitCpp/Test.h>

#include "Range.h"

//=============================================================================
TEST(RangeIter, equality)
{
  Range<int> range(2);
  RangeIter<int> iter_1(&range);
  RangeIter<int> iter_2(&range);
  RangeIter<int> end(nullptr);
  TEST_EQUAL(iter_1, iter_2, "Items should be equal");
  TEST_NOT_EQUAL(iter_1, end, "iter_1 is not at the end.");
  ++range;
  ++range;
  TEST_FALSE(range);
  TEST_EQUAL(end, iter_1, "iter_1 is at the end.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_DELEGATING_CONSTRUCTOR)
#endif
