//=============================================================================
//
// 

#include <iostream>
#include <assert.h>

#include "UnitTest.h"
#include "Range.h"

//=============================================================================
class utest_Range : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_int();
    test_step();
    test_for();
    test_range_based_for();
    test_STL_style_for();
  }

private:

  void test_int();

  void test_step();

  void test_for();

  void test_range_based_for();

  void test_STL_style_for();

};

//=============================================================================
void utest_Range::test_range_based_for()
{
  print(DGC_CURRENT_FUNCTION);
  float check = -5.5;
  for (float f: Range<float>(-5.0, 10.0, 0.5)) {
    check += 0.5;
    test(f == check, "Wrong value for ", f, " expecting ", check, ".");
  }
  test(check == 9.5, "Wrong limit. Expecting 9.5, got ", check, ".");
}

//=============================================================================
void utest_Range::test_STL_style_for()
{
  print(DGC_CURRENT_FUNCTION);
  Range<int> range(5);
  int i = -1;
  for (auto it = std::begin(range); it != std::end(range); ++it) {
    ++i;
    test(i == (*it), "Wrong value for ", i);
  }
  test(i == 4, "Wrong limit.");
}

//=============================================================================
void utest_Range::test_int()
{
  print(DGC_CURRENT_FUNCTION);
  Range<int> range(5);

  test(range, "Range should be good");
  test(range() == 0, "first element should be 0");
  ++range;
  
  test(range, "Range should be good");
  test(range() == 1, "next element should be 1");
  ++range;
  
  test(range, "Range should be good");
  test(range() == 2, "next element should be 2");
  ++range;
  
  test(range, "Range should be good");
  test(range() == 3, "next element should be 3");
  ++range;
  
  test(range, "Range should be good");
  test(range() == 4, "next element should be 4");
  ++range;

  test(!range, "Range should not be good.");
}

//=============================================================================
void utest_Range::test_step()
{
  print(DGC_CURRENT_FUNCTION);
  Range<double> range(0, 5, 0.5);
  for (double d = 0; d < 5; d += 0.5) {
    test(range() == d, "Range at ", d, " is wrong.");
    test(range, "Range at ", d, " should be good.");
    ++range;
  }
  test(!range, "Range should be bad.");
}

//=============================================================================
void utest_Range::test_for()
{
  // This is the example use of Range<T>
  print(DGC_CURRENT_FUNCTION);
  int i = -1;
  for (Range<int> range(5); range; ++range) {
    ++i;
    test(range() == i, "Wrong value for ", i, "th.");
  }
  test(i == 4, "Wrong limit for i.");
}

//=============================================================================
int main() {
  utest_Range test;
  test.run_tests();
  return 0;
}

