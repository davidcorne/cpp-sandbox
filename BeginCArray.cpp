//=============================================================================
//
// 
#include "Capabilities.h"
#ifdef VARIADIC_TEMPLATES
#include "UnitTest.h"

#include <vector>

//=============================================================================
class utest_BeginCArray : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_iterate_c_array();
    test_take_sum();
  }

private:

  void test_iterate_c_array();
  void test_take_sum();

};

//=============================================================================
template <typename T, typename Iterable>
T take_sum(T start, const Iterable& iterable)
{
  T sum = start;
  for (T i: iterable) {
    sum += i;
  }
  return sum;
}

//=============================================================================
void utest_BeginCArray::test_take_sum()
{
  print(DGC_CURRENT_FUNCTION);
  double buffer[] = {0.1, 1.2, 2.3, 3.4, 4.5};
  std::vector<double> vector = {0.1, 1.2, 2.3, 3.4, 4.5};
  double sum_1 = take_sum(0, buffer);
  double sum_2 = take_sum(0, vector);
  test(sum_1 == sum_2, "Sums should be the same.");
  
}

//=============================================================================
void utest_BeginCArray::test_iterate_c_array()
{
  print(DGC_CURRENT_FUNCTION);
  int buffer[5] = {0, 1, 2, 3, 4};
  int sum = 0;
  for (auto it = std::begin(buffer); it != std::end(buffer); ++it) {
    sum += *it;
  }
  test(sum == 10, "0 + 1 + 2 + 3 + 4 == 10");
  sum = 0;
  for (int i: buffer) {
    sum += i;
  }
  test(sum == 10, "0 + 1 + 2 + 3 + 4 == 10");

  sum = 0;
  for (int* it = &buffer[0]; it != &buffer[5]; ++it) {
    sum += *it;
  }
  test(sum == 10, "0 + 1 + 2 + 3 + 4 == 10");
}

//=============================================================================
int main() {
  utest_BeginCArray test;
  test.run_tests();
  return 0;
}
#else
UNSUPPORTED_FEATURE_MAIN
#endif
