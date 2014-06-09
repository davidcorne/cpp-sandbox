//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"
#include "Range.h"

//=============================================================================
class utest_RangeIter : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_equality();
  }

private:

  void test_equality();

};

//=============================================================================
void utest_RangeIter::test_equality()
{
  print(DGC_CURRENT_FUNCTION);
  Range<int> range(2);
  RangeIter<int> iter_1(&range);
  RangeIter<int> iter_2(&range);
  RangeIter<int> end(nullptr);
  test(iter_1 == iter_2, "Items should be equal");
  test(iter_1 != end, "iter_1 is not at the end.");
  ++range;
  ++range;
  assert(range == false);
  test(end == iter_1, "iter_1 is at the end.");
}

//=============================================================================
int main() {
  utest_RangeIter test;
  test.run_tests();
  return 0;
}
