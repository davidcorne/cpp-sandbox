//=============================================================================
// Accessing an element of an array via ptr[3] is actually just short for
// *(ptr + 3). This can be equivalently written as *(3 + ptr) and therefore
// as 3[ptr]

#include "UnitTest.h"

using namespace std;

//=============================================================================
class utest_OddArrayAccess : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_access();
    test_loop();
  }

private:

  void test_access();
  void test_loop();

};

//=============================================================================
void utest_OddArrayAccess::test_access()
{
  print(DGC_CURRENT_FUNCTION);
  int array[2] = {0,1};
  test(array[0] == 0[array], "Odd array access works.");
  test(array[1] == 1[array], "Odd array access works.");
  test(0 == 0[array], "Odd array access works.");
  test(1 == 1[array], "Odd array access works.");

}

//=============================================================================
void utest_OddArrayAccess::test_loop()
{
  print(DGC_CURRENT_FUNCTION);
  const int length = 10;
  int array[length];
  for (int i = 0; i < length; ++i) {
    array[i] = i;
  }
  for (int i = 0; i < length; ++i) {
    test(i[array] == i, "Correct value set and read.");
  }
  
}

//=============================================================================
int main() {
  utest_OddArrayAccess test;
  test.run_tests();
  return 0;
}
