//=============================================================================
//
// Passing vectors to C style APIs, item 16 Effective STL.

#include <iostream>
#include <vector>

#include <UnitCpp.h>

//=============================================================================
int legecy_sum(const int* array, size_t size)
{
  int sum = 0;
  for (size_t i = 0; i < size; ++i) {
    sum += array[i];
  }
  return sum;
}

//=============================================================================
void fill_arrray(int* array, size_t size)
{
  for (int i = 0; i < static_cast<int>(size); ++i) {
    array[i] = i * i;
  }
}

//=============================================================================
TEST(VectorToCArray, sum)
{
  std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  TEST_EQUAL(legecy_sum(array.data(), array.size()), 55, "Wrong sum");
}

//=============================================================================
TEST(VectorToCArray, fill_array)
{
  // fill an array of size 10 with -1
  std::vector<int> array(10, -1);
  fill_arrray(array.data(), array.size());
  TEST_EQUAL(array[0], 0, "Array element wrong.");
  TEST_EQUAL(array[1], 1, "Array element wrong.");
  TEST_EQUAL(array[2], 4, "Array element wrong.");
  TEST_EQUAL(array[3], 9, "Array element wrong.");
  TEST_EQUAL(array[4], 16, "Array element wrong.");
  TEST_EQUAL(array[5], 25, "Array element wrong.");
  TEST_EQUAL(array[6], 36, "Array element wrong.");
  TEST_EQUAL(array[7], 49, "Array element wrong.");
  TEST_EQUAL(array[8], 64, "Array element wrong.");
  TEST_EQUAL(array[9], 81, "Array element wrong.");
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
