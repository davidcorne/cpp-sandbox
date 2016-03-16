//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS
#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include <UnitCpp.h>

#include "IteratorCreators.h"
#include "size_t_literal.h"

//=============================================================================
template <typename T, typename OutputIterator>
void transform(
  std::function<T(T)> functor,
  Iterator<T> iter,
  OutputIterator ouput
)
{
  while (++iter) {
    *ouput = functor(iter());
    ++ouput;
  }
}
  
//=============================================================================
TEST(OutputIterator, transform_overwrite)
{
  std::vector<int> in_vector = {1, 2, 3, 4};
  std::function<int(int)> square = [](int in) -> int {
    return in * in;
  };
  Iterator<int> iter = IteratorCreators::iter(in_vector);
  transform(square, iter, std::begin(in_vector));
  TEST_EQUAL(in_vector[0], 1, "1*1 == 1, not ", in_vector[0]);
  TEST_EQUAL(in_vector[1], 4, "2*2 == 4, not ", in_vector[1]);
  TEST_EQUAL(in_vector[2], 9, "3*3 == 9, not ", in_vector[2]);
  TEST_EQUAL(in_vector[3], 16, "4*4 == 16, not ", in_vector[3]);
}

//=============================================================================
TEST(OutputIterator, transform_int)
{
  std::vector<int> in_vector = {1, 2, 3, 4};
  std::vector<int> results;
  std::function<int(int)> double_int = [](int in) -> int {
    return 2 * in;
  };
  Iterator<int> iter = IteratorCreators::iter(in_vector);
  transform(double_int, iter, std::back_inserter(results));
  TEST_EQUAL(results.size(), 4_st, "Wrong size ", results.size(), " != 4");
  TEST_EQUAL(results[0], 2, "1st element should be 2.");
  TEST_EQUAL(results[1], 4, "2nd element should be 4.");
  TEST_EQUAL(results[2], 6, "3rd element should be 6.");
  TEST_EQUAL(results[3], 8, "4th element should be 8.");
}

//=============================================================================
TEST(OutputIterator, transform_string)
{
  std::vector<std::string> in_vector = {"hi", "ThEr"};
  std::vector<std::string> results;
  std::function<std::string(std::string)> first =
    [](std::string in) -> std::string
    {
      return std::string(1, in[0]);
    };
  Iterator<std::string> iter = IteratorCreators::iter(in_vector);
  transform(first, iter, std::back_inserter(results));
  TEST_EQUAL(results.size(), 2_st, "Wrong size ", results.size(), " != 2.");
  TEST_EQUAL(results[0], "h", "1st element wrong.");
  TEST_EQUAL(results[1], "T", "2nd element wrong.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif
