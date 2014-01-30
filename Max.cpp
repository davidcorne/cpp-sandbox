//=============================================================================
//
// 

#include "UnitTest.h"

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
class utest_Max : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_max_int();
    test_min_int();
    test_max_double();
  }

private:

  void test_max_int();
  void test_min_int();
  void test_max_double();
};

//=============================================================================
void utest_Max::test_max_int()
{
  print(DGC_CURRENT_FUNCTION);
  // Template type deduction works out to use max<int>
  test(max(2, 3) == 3, "Max value of (2, 3) incorrect.");
  test(max(2, -3) == 2, "Max value of (2, -3) incorrect.");
  test(max(2, 300000) == 300000, "Max value of (2, 300000) incorrect.");
  test(max(0, 0) == 0, "Max value of (0, 0) incorrect.");

  int i = 0;
  int j = 5;
  test(max(i, j) == j, "Template deduction with variables.");
}

//=============================================================================
void utest_Max::test_max_double()
{
  print(DGC_CURRENT_FUNCTION);
  test(max(2.0, 1.234) == 2.0, "Max value of (2, 1.234) incorrect.");

  double a = 0.8;
  double b = -3.14;
  test(max(a, b) == a, "Template deduction with variables.");
}

//=============================================================================
void utest_Max::test_min_int()
{
  print(DGC_CURRENT_FUNCTION);
  test(min(2, 3) == 2, "Min value of (2, 3) incorrect.");
  test(min(2, -3) == -3, "Min value of (2, -3) incorrect.");
  test(min(2, 300000) == 2, "Min value of (2, 300000) incorrect.");
  test(min(0, 0) == 0, "Min value of (0, 0) incorrect.");

}

//=============================================================================
int main() {
  utest_Max test;
  test.run_tests();
  return 0;
}
