//=============================================================================
//
// 

#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include "UnitTest.h"
#include "IteratorCreators.h"

//=============================================================================
template <typename T, typename OutputIterator>
void transform(
  std::function<T(T)> functor,
  Iterator<T> iter,
  OutputIterator ouput
)
{
  while (++iter) {
    *ouput = functor(iter());
    ++ouput;
  }
}
  
//=============================================================================
class utest_OutputIterator : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_transform_int();
    test_transform_overwrite();
    test_transform_string();
  }

private:

  void test_transform_int();
  void test_transform_overwrite();
  void test_transform_string();

};

//=============================================================================
void utest_OutputIterator::test_transform_overwrite()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<int> in_vector = {1, 2, 3, 4};
  std::function<int(int)> square = [](int in) -> int {
    return in * in;
  };
  Iterator<int> iter = IteratorCreators::iter(in_vector);
  transform(square, iter, std::begin(in_vector));
  test(in_vector[0] == 1, "1*1 == 1, not ", in_vector[0]);
  test(in_vector[1] == 4, "2*2 == 4, not ", in_vector[1]);
  test(in_vector[2] == 9, "3*3 == 9, not ", in_vector[2]);
  test(in_vector[3] == 16, "4*4 == 16, not ", in_vector[3]);
}

//=============================================================================
void utest_OutputIterator::test_transform_int()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<int> in_vector = {1, 2, 3, 4};
  std::vector<int> results;
  std::function<int(int)> double_int = [](int in) -> int {
    return 2 * in;
  };
  Iterator<int> iter = IteratorCreators::iter(in_vector);
  transform(double_int, iter, std::back_inserter(results));
  test(results.size() == 4, "Wrong size ", results.size(), " != 4");
  test(results[0] == 2, "1st element should be 2.");
  test(results[1] == 4, "2nd element should be 4.");
  test(results[2] == 6, "3rd element should be 6.");
  test(results[3] == 8, "4th element should be 8.");
}

//=============================================================================
void utest_OutputIterator::test_transform_string()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<std::string> in_vector = {"hi", "ThEr"};
  std::vector<std::string> results;
  std::function<std::string(std::string)> first =
    [](std::string in) -> std::string
    {
      return std::string(1, in[0]);
    };
  Iterator<std::string> iter = IteratorCreators::iter(in_vector);
  transform(first, iter, std::back_inserter(results));
  test(results.size() == 2, "Wrong size ", results.size(), " != 2.");
  test(results[0] == "h", "1st element wrong.");
  test(results[1] == "T", "2nd element wrong.");
}

//=============================================================================
int main() {
  utest_OutputIterator test;
  test.run_tests();
  return 0;
}
