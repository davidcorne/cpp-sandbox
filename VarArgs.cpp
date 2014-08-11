//=============================================================================
//
// 

#include <iostream>
#include <stdarg.h>

#include "UnitTest.h"

//=============================================================================
class VarArgs {
public:

  VarArgs(int n, ...)
  {
    va_list list;
    va_start(list, n);
    for (int i = 0; i < n; ++i) {
      const char* val = va_arg(list, const char*);
      std::cout << val << std::endl;
    }
    va_end(list);
  }
  
private:
  friend class utest_VarArgs;
};

//=============================================================================
class utest_VarArgs : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_ctor();
  }

private:

  void test_ctor();

};

//=============================================================================
void utest_VarArgs::test_ctor()
{
  print(DGC_CURRENT_FUNCTION);
  VarArgs args(3, "Hi", "0.5", "anything");
}

//=============================================================================
int main() {
  utest_VarArgs test;
  test.run_tests();
  return 0;
}
