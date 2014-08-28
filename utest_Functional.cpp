#include <UnitCpp/Test.h>

#include "Capabilities.h"
#ifdef GENERIC_LAMBDAS

#include "Functional.h"

//=============================================================================
TEST(Functional, while_func)
{
  int i = 0;
  auto condition = [&i](){return i < 5;};
  auto func = [&i](){++i;};
  while_func(condition, func);
  TEST_EQUAL(i, 5);
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(
    argc,
    argv
  );
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
