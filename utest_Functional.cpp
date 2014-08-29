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
TEST(Functional, if_func)
{
  auto one = id(1);
  auto two = id(2);
  auto true_func = id(true);
  auto false_func = id(false);
  TEST_EQUAL(if_func(true_func, one, two)()(), 1);
  TEST_EQUAL(if_func(false_func, one, two)()(), 2);
}

//=============================================================================
TEST(Functional, id)
{
  auto ok = id(std::string("Ok"));
  TEST_EQUAL(ok(), "Ok");

  auto pi = id(3.14159265359);
  TEST_APPROX_EQUAL(pi(), 3.14, 0.005);
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
