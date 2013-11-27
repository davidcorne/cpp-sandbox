//=============================================================================
//
// 

#include <iostream>
#include <functional>

#include "../UnitTest.h"

using namespace std;

//=============================================================================
function<int(void)> counter()
{
  static int count = 0;
  function<int(void)> increment = [&]() -> int {
    cout << count << endl;
    ++count;
    cout << count << endl;
    return count;
  };
  return increment;
}

//=============================================================================
class utest_Closure : public UnitTest {
public:

  void run_tests() {
    print(DGC_CURRENT_FUNCTION);
    test_counter();
  }

private:

  void test_counter();

};

//=============================================================================
void utest_Closure::test_counter()
{
  print(__FUNCTION__);
  function<int(void)> func = counter();
  test(func() == 1, "First call should be 1");
  test(func() == 2, "Second call should be 2");
  test(func() == 3, "Third call should be 3");
  test(func() == 4, "Fourth call should be 4");
}

//=============================================================================
int main() {
  utest_Closure test;
  test.run_tests();
  return 0;
}
