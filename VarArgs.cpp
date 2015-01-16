//=============================================================================
//
// 

#include <iostream>
#include <stdarg.h>

#include <UnitCpp.h>

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
TEST(VarArgs, constructor)
{
  VarArgs args(3, "Hi", "0.5", "anything");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
