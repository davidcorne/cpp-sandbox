//=============================================================================
//
// 

#include <UnitCpp/Test.h>

//=============================================================================
template<typename T>
T max(T a, T b)
{
  return a < b ? b : a;
}

//=============================================================================
template<typename T>
T min(T a, T b)
{
  return a < b ? a : b;
}

//=============================================================================
TEST(Max, int)
{
  // Template type deduction works out to use max<int>
  TEST_EQUAL(max(2, 3), 3, "Max value of (2, 3) incorrect.");
  TEST_EQUAL(max(2, -3), 2, "Max value of (2, -3) incorrect.");
  TEST_EQUAL(max(2, 300000), 300000, "Max value of (2, 300000) incorrect.");
  TEST_EQUAL(max(0, 0), 0, "Max value of (0, 0) incorrect.");

  int i = 0;
  int j = 5;
  TEST_EQUAL(max(i, j), j, "Template deduction with variables.");
}

//=============================================================================
TEST(Max, double)
{
  TEST_EQUAL(max(2.0, 1.234), 2.0, "Max value of (2, 1.234) incorrect.");

  double a = 0.8;
  double b = -3.14;
  TEST_EQUAL(max(a, b), a, "Template deduction with variables.");
}

//=============================================================================
TEST(Min, int)
{
  TEST_EQUAL(min(2, 3), 2, "Min value of (2, 3) incorrect.");
  TEST_EQUAL(min(2, -3), -3, "Min value of (2, -3) incorrect.");
  TEST_EQUAL(min(2, 300000), 2, "Min value of (2, 300000) incorrect.");
  TEST_EQUAL(min(0, 0), 0, "Min value of (0, 0) incorrect.");

}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
