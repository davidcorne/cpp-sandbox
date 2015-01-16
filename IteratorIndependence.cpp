//=============================================================================
//
// Very much inspired by this:
// http://www.drdobbs.com/typedefs-and-iterators-if-youve-got-em-u/184401853

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS
#include <iostream>
#include <vector>
#include <list>
#include <set>

#include <UnitCpp.h>

//=============================================================================
class IntSummer {
public:

  template <typename IntIter>
  int sum(IntIter first, IntIter last) const;
  
private:
  friend class utest_IntSummer;
};

//=============================================================================
class GeneralSummer {
public:

  template <typename ITER>
  typename ITER::value_type sum(ITER first, ITER last) const;
};

//=============================================================================
TEST(IntSummer, vector)
{
  IntSummer summer;
  std::vector<int> array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int sum = summer.sum(std::begin(array), std::end(array));
  TEST_EQUAL(sum, 55, "Incorrect sum.");

  GeneralSummer general_summer;
  int general_sum = general_summer.sum(std::begin(array), std::end(array));
  TEST_EQUAL(general_sum, sum, "Sums should be the same.");
}

//=============================================================================
TEST(IntSummer, set)
{
  IntSummer summer;
  std::set<int> array = {0, 1, 1, 1, 2};
  int sum = summer.sum(std::begin(array), std::end(array));
  TEST_EQUAL(sum, 3, "Incorrect sum.");
}

//=============================================================================
TEST(IntSummer, list)
{
  IntSummer summer;
  std::list<int> array = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
  int sum = summer.sum(std::begin(array), std::end(array));
  TEST_EQUAL(sum, -55, "Incorrect sum.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

template <typename IntIter>
int IntSummer::sum(IntIter first, IntIter last) const
{
  int result = 0;
  for (IntIter iter = first; iter != last; ++iter) {
    result += *iter;
  }
  return result;
}

//=============================================================================
template <typename ITER>
typename ITER::value_type GeneralSummer::sum(ITER first, ITER last) const
{
  typename ITER::value_type total = 0;
  for (auto it = first; it != last; ++it) {
    total = total + *it;
  }
  return total;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif

