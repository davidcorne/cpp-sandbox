#include <UnitCpp/Test.h>

#include "Capabilities.h"
#if CAPABILITY_GENERIC_LAMBDAS

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
  auto one = fnc::unit(1);
  auto two = fnc::unit(2);
  auto true_func = fnc::unit(true);
  auto false_func = fnc::unit(false);
  TEST_EQUAL(fnc::if_func(true_func, one, two)()(), 1);
  TEST_EQUAL(fnc::if_func(false_func, one, two)()(), 2);
}

//=============================================================================
TEST(Functional, unit)
{
  auto ok = fnc::unit(std::string("Ok"));
  TEST_EQUAL(ok(), "Ok");

  auto pi = fnc::unit(3.14159265359);
  TEST_APPROX_EQUAL(pi(), 3.14, 0.005);
}

//=============================================================================
TEST(Functional, null)
{
  fnc::null();
}

//=============================================================================
TEST(Functional, currying)
{
  auto increment = fnc::curry(fnc::add, 1);
  TEST_EQUAL(increment(5)(), 6);

  auto to_ten = fnc::curry(fnc::range, 0, 10);

  int sum = 0;
  to_ten([&sum](auto i){sum += i;});
  TEST_EQUAL(sum, 45);
  
  auto add_three = [](auto i, auto j, auto k) {return i + j + k;};
  TEST_EQUAL(add_three(1, 2, 3), 6);
  auto add_ten = fnc::curry(add_three, 4, 6);
  TEST_EQUAL(add_ten(4), 14);
}

//=============================================================================
TEST(Functional, stringify)
{
  TEST_EQUAL(fnc::stringify(5)(), "5");
}

//=============================================================================
TEST(Functional, bind)
{
  TEST_EQUAL(fnc::bind(fnc::unit(15))(fnc::stringify)(), "15");
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
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_GENERIC_LAMBDAS)
#endif
