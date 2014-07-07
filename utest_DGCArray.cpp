//=============================================================================
//
// 

#include "DGCArray.h"
#include "IteratorCreators.h"
#include "UnitTest.h"

//=============================================================================
class utest_DGCArray : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_ctor();
    test_iter();
  }

private:

  void test_ctor();
  void test_iter();

};

//=============================================================================
void utest_DGCArray::test_ctor()
{
  print(DGC_CURRENT_FUNCTION);
  DGC::Array<int> array(5, 9);
  test(array.size() == 5, "Array has incorrect size.");
  test(array[0] == 9, "Array has an incorrect value.");
  test(array[1] == 9, "Array has an incorrect value.");
  test(array[2] == 9, "Array has an incorrect value.");
  test(array[3] == 9, "Array has an incorrect value.");
  test(array[4] == 9, "Array has an incorrect value.");

}

//=============================================================================
void utest_DGCArray::test_iter()
{
  print(DGC_CURRENT_FUNCTION);
  DGC::Array<double> array(10, 3.14);
  Iterator<double> iter = IteratorCreators::iter(array);
  int count = 0;
  while (++iter) {
    test(iter() == 3.14, "All should have value 3.14.");
    ++count;
  }
  test(count == 10, "Should be 10 values.");
}

//=============================================================================
int main() {
  utest_DGCArray test;
  test.run_tests();
  return 0;
}
