//=============================================================================
//
// 

#include <iostream>
#include <vector>

#include "UnitTest.h"

//=============================================================================
class RangeBasedFor {
public:

private:
  friend class utest_RangeBasedFor;
};

//=============================================================================
class utest_RangeBasedFor : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_vector();
  }

private:

  void test_vector();

};

//=============================================================================
void utest_RangeBasedFor::test_vector()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  int count = 0;
  for (auto i: v) {
    test(i == count, "Wrong count");
    ++count;
  }

  count = 0;
  for (int i: v) {
    test(i == count, "Wrong count");
    ++count;
  }
}

//=============================================================================
int main() {
  utest_RangeBasedFor test;
  test.run_tests();
  return 0;
}
