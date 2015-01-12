//=============================================================================
// Trying out a little type deduction, algorithms independent of iterator type
// and trailing return type function syntax.

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS

#include <iostream>
#include <string>
#include <vector>

//=============================================================================
template <typename ITER>
auto summation(
  ITER begin, ITER end, typename ITER::value_type start=0
) -> typename ITER::value_type;

//=============================================================================
int main()
{
  std::vector<int> array = {1, 2, 3, 4};
  std::cout << summation(std::begin(array), std::end(array)) << std::endl;
  std::cout << summation(std::begin(array), std::end(array), 40) << std::endl;

  std::vector<std::string> strings =
    {"this ", "is ", "not ", "a " "sentence."};
  std::cout << summation(std::begin(strings), std::end(strings), "") << std::endl;
};

//=============================================================================
template <typename ITER>
auto summation(ITER begin, ITER end, typename ITER::value_type start) -> typename ITER::value_type
{
  typename ITER::value_type result = start;
  for (ITER it = begin; it != end; ++it) {
    result = result + *it;
  }
  return result;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif
