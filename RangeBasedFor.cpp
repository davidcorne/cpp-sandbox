//=============================================================================
//
// 

#include "Capabilities.h"

#if CAPABILITY_RANGE_BASE_FOR
#include <iostream>
#include <vector>

#include <UnitCpp/Test.h>

//=============================================================================
TEST(RangeBasedFor, vector)
{
  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  int count = 0;
  for (auto i: v) {
    TEST_EQUAL(i, count, "Wrong count");
    ++count;
  }

  count = 0;
  for (int i: v) {
    TEST_EQUAL(i, count, "Wrong count");
    ++count;
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_RANGE_BASE_FOR)
#endif
