//=============================================================================
//
// 

#include <iostream>
#include <functional>
#include <vector>

#include "UnitTest.h"
#include "IteratorCreators.h"

//=============================================================================
template <typename OutputIterator>
void transform(
  std::function<int(int)> functor,
  Iterator<int> iter,
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
    test_transform();
  }

private:

  void test_transform();

};

//=============================================================================
void utest_OutputIterator::test_transform()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<int> in_vector = {1, 2, 3, 4};
  std::vector<int> result_vector;
  std::function<int(int)> double_int = [](int in) -> int {
    return 2 * in;
  };
  Iterator<int> iter = IteratorCreators::iter(in_vector);
  transform(double_int, iter, std::back_inserter(result_vector));
  test(result_vector.size() == 4, "Wrong size ",result_vector.size(), " != 4");
  test(result_vector[0] == 2, "1st element should be 2.");
  test(result_vector[1] == 4, "2nd element should be 4.");
  test(result_vector[2] == 6, "3rd element should be 6.");
  test(result_vector[3] == 8, "4th element should be 8.");
}

//=============================================================================
int main() {
  utest_OutputIterator test;
  test.run_tests();
  return 0;
}
