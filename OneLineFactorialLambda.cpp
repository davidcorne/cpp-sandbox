//=============================================================================
//
// 
#include <functional>

#include <UnitCpp/Test.h>

//=============================================================================
std::function<int(int)> factorial = [](int number)->int {
  return number < 2 ? 1 : number * factorial(number - 1);
};

//=============================================================================
TEST(OneLineFactorialLambda, lambda)
{
  TEST_EQUAL(factorial(1), 1);
  TEST_EQUAL(factorial(2), 2);
  TEST_EQUAL(factorial(3), 6);
  TEST_EQUAL(factorial(4), 24);
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
