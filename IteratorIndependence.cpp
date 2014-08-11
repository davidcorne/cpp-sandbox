//=============================================================================
//
// Very much inspired by this:
// http://www.drdobbs.com/typedefs-and-iterators-if-youve-got-em-u/184401853

#include <iostream>
#include <vector>
#include <list>
#include <set>

#include "UnitTest.h"

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
class utest_IntSummer : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_list();
    test_vector();
    test_set();
  }

private:

  void test_vector();

  void test_list();

  void test_set();
  
};

//=============================================================================
void utest_IntSummer::test_vector()
{
  print(DGC_CURRENT_FUNCTION);
  IntSummer summer;
  std::vector<int> array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int sum = summer.sum(std::begin(array), std::end(array));
  test(sum == 55, "Incorrect sum.");

  GeneralSummer general_summer;
  int general_sum = general_summer.sum(std::begin(array), std::end(array));
  test(general_sum == sum, "Sums should be the same.");
}

//=============================================================================
void utest_IntSummer::test_set()
{
  print(DGC_CURRENT_FUNCTION);
  IntSummer summer;
  std::set<int> array = {0, 1, 1, 1, 2};
  int sum = summer.sum(std::begin(array), std::end(array));
  test(sum == 3, "Incorrect sum.");
}

//=============================================================================
void utest_IntSummer::test_list()
{
  print(DGC_CURRENT_FUNCTION);
  IntSummer summer;
  std::list<int> array = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
  int sum = summer.sum(std::begin(array), std::end(array));
  test(sum == -55, "Incorrect sum.");
}

//=============================================================================
int main() {
  utest_IntSummer test;
  test.run_tests();
  return 0;
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
