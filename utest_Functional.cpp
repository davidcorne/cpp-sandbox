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
  fnc::while_func(condition, func)();
  TEST_EQUAL(i, 5);
}

//=============================================================================
TEST(Functional, if_func)
{
  auto one = fnc::id(1);
  auto two = fnc::id(2);
  auto true_func = fnc::id(true);
  auto false_func = fnc::id(false);
  TEST_EQUAL(fnc::if_func(true_func, one, two)()(), 1);
  TEST_EQUAL(fnc::if_func(false_func, one, two)()(), 2);
}

//=============================================================================
TEST(Functional, id)
{
  auto ok = fnc::id(std::string("Ok"));
  TEST_EQUAL(ok(), "Ok");

  auto pi = fnc::id(3.14159265359);
  TEST_APPROX_EQUAL(pi(), 3.14, 0.005);
}

//=============================================================================
TEST(Functional, null)
{
  fnc::null();
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
