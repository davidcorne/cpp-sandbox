//=============================================================================
//
// Very much inspired by this:
// http://www.drdobbs.com/typedefs-and-iterators-if-youve-got-em-u/184401853

#include <iostream>
#include <vector>
#include <list>
#include <set>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class IntSummer {
public:

  template <typename IntIter>
  int sum(IntIter first, IntIter last) const;
  
private:
  friend class utest_IntSummer;
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
  vector<int> array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int sum = summer.sum(begin(array), end(array));
  test(sum == 55, "Incorrect sum.");
}

//=============================================================================
void utest_IntSummer::test_set()
{
  print(DGC_CURRENT_FUNCTION);
  IntSummer summer;
  set<int> array = {0, 1, 1, 1, 2};
  int sum = summer.sum(begin(array), end(array));
  test(sum == 3, "Incorrect sum.");
}

//=============================================================================
void utest_IntSummer::test_list()
{
  print(DGC_CURRENT_FUNCTION);
  IntSummer summer;
  list<int> array = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
  int sum = summer.sum(begin(array), end(array));
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
