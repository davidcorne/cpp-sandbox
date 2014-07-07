//=============================================================================
//
// 

#include <vector>

#include "UnitTest.h"
#include "Enumeration.h"

//=============================================================================
class utest_Enumeration : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_vector();
  }

private:

  void test_vector();

};

//=============================================================================
void utest_Enumeration::test_vector()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<double> array = {0, 2, 4, 6, 8};
  int i = 0;
  for (auto pair: Enumeration<std::vector<double> >(array)) {
    test(pair.first == i, "Wrong index.");
    test(pair.second == (double)(i * 2), "Wrong value.");
    ++i;
  }

}

//=============================================================================
int main() {
  utest_Enumeration test;
  test.run_tests();
  return 0;
}