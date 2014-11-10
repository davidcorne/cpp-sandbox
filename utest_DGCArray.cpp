//=============================================================================
//
// 

#include "DGCArray.h"
#include "IteratorCreators.h"

#include <UnitCpp/Test.h>

//=============================================================================
TEST(DGCArray, constructor)
{
  DGC::Array<int> array(5, 9);
  TEST_EQUAL(array.size(), 5, "Array has incorrect size.");
  TEST_EQUAL(array[0], 9, "Array has an incorrect value.");
  TEST_EQUAL(array[1], 9, "Array has an incorrect value.");
  TEST_EQUAL(array[2], 9, "Array has an incorrect value.");
  TEST_EQUAL(array[3], 9, "Array has an incorrect value.");
  TEST_EQUAL(array[4], 9, "Array has an incorrect value.");

}

//=============================================================================
TEST(DGCArray, iter)
{
  DGC::Array<double> array(10, 3.14);
  Iterator<double> iter = IteratorCreators::iter(array);
  int count = 0;
  while (++iter) {
    TEST_EQUAL(iter(), 3.14, "All should have value 3.14.");
    ++count;
  }
  TEST_EQUAL(count, 10, "Should be 10 values.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
