//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_INITIALISER_LISTS
#include <vector>

#include <UnitCpp/Test.h>

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
TEST(BeginCArray, take_sum)
{
  double buffer[] = {0.1, 1.2, 2.3, 3.4, 4.5};
  std::vector<double> vector = {0.1, 1.2, 2.3, 3.4, 4.5};
  double sum_1 = take_sum(0, buffer);
  double sum_2 = take_sum(0, vector);
  TEST_EQUAL(sum_1, sum_2, "Sums should be the same.");
}

//=============================================================================
TEST(BeginCArray, iterate_c_array)
{
  int buffer[5] = {0, 1, 2, 3, 4};
  int sum = 0;
  for (auto it = std::begin(buffer); it != std::end(buffer); ++it) {
    sum += *it;
  }
  TEST_EQUAL(sum, 10, "0 + 1 + 2 + 3 + 4 == 10");
  sum = 0;
  for (int i: buffer) {
    sum += i;
  }
  TEST_EQUAL(sum, 10, "0 + 1 + 2 + 3 + 4 == 10");

  sum = 0;
  for (int* it = &buffer[0]; it != &buffer[5]; ++it) {
    sum += *it;
  }
  TEST_EQUAL(sum, 10, "0 + 1 + 2 + 3 + 4 == 10");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif
