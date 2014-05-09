//=============================================================================
//
// Passing vectors to C style APIs, item 16 Effective STL.

#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

//=============================================================================
int legecy_sum(const int* array, int size)
{
  int sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += array[i];
  }
  return sum;
}

//=============================================================================
void fill_arrray(int* array, int size)
{
  for (int i = 0; i < size; ++i) {
    array[i] = i * i;
  }
}

//=============================================================================
class utest_VectorToCArray : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_sum();
    test_fill_array();
  }

private:

  void test_sum();
  void test_fill_array();

};

//=============================================================================
void utest_VectorToCArray::test_sum()
{
  print(DGC_CURRENT_FUNCTION);
  vector<int> array;
  array.push_back(1);
  array.push_back(2);
  array.push_back(3);
  array.push_back(4);
  array.push_back(5);
  array.push_back(6);
  array.push_back(7);
  array.push_back(8);
  array.push_back(9);
  array.push_back(10);
  test(legecy_sum(&array[0], array.size()) == 55, "Wrong sum");
}

//=============================================================================
void utest_VectorToCArray::test_fill_array()
{
  print(DGC_CURRENT_FUNCTION);
  // fill an array of size 10 with -1
  vector<int> array(10, -1);
  fill_arrray(&array[0], array.size());
  test(array[0] == 0, "Array element wrong.");
  test(array[1] == 1, "Array element wrong.");
  test(array[2] == 4, "Array element wrong.");
  test(array[3] == 9, "Array element wrong.");
  test(array[4] == 16, "Array element wrong.");
  test(array[5] == 25, "Array element wrong.");
  test(array[6] == 36, "Array element wrong.");
  test(array[7] == 49, "Array element wrong.");
  test(array[8] == 64, "Array element wrong.");
  test(array[9] == 81, "Array element wrong.");
}

//=============================================================================
int main() {
  utest_VectorToCArray test;
  test.run_tests();
  return 0;
}
