//=============================================================================
//
// 

#include <string>

#include "UnitTest.h"

//=============================================================================
class Difference {
public:

private:
};

//=============================================================================
Difference difference(std::string one, std::string two)
{
  return Difference();
}

//=============================================================================
class utest_Difference : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_difference();
  }

private:

  void test_difference();

};

//=============================================================================
void utest_Difference::test_difference()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
int main() {
  utest_Difference test;
  test.run_tests();
  return 0;
}
