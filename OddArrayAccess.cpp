//=============================================================================
// Accessing an element of an array via ptr[3] is actually just short for
// *(ptr + 3). This can be equivalently written as *(3 + ptr) and therefore
// as 3[ptr]

#include <UnitCpp/Test.h>

//=============================================================================
TEST(OddArrayAccess, access)
{
  int array[2] = {0,1};
  TEST_EQUAL(array[0], 0[array], "Odd array access works.");
  TEST_EQUAL(array[1], 1[array], "Odd array access works.");
  TEST_EQUAL(0, 0[array], "Odd array access works.");
  TEST_EQUAL(1, 1[array], "Odd array access works.");

}

//=============================================================================
TEST(OddArrayAccess, loop)
{
  const int length = 10;
  int array[length];
  for (int i = 0; i < length; ++i) {
    array[i] = i;
  }
  for (int i = 0; i < length; ++i) {
    TEST_EQUAL(i[array], i, "Correct value set and read.");
  }
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
