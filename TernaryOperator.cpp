//=============================================================================
//
// 

#include <UnitCpp.h>

//=============================================================================
TEST(TernaryOperator, test)
{
  int i = true ? 0 : 1;
  TEST_EQUAL(i, 0);
  int j = false ? 0 : 1;
  TEST_EQUAL(j, 1);
  // You can also use the ternary operator in lvalues.
  (true ? i : j) = 5;
  TEST_EQUAL(i, 5);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
