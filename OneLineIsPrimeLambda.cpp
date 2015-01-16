//=============================================================================
//
// 
#include <functional>
#include <cmath>

#include <UnitCpp.h>


// These are obviously terrible lambdas. This is to show very complicated one
// line lambda functions. To get them on 1 line I have sacrificed variable
// naming. Also loop_factors clearly is not a well conceived function.

//=============================================================================
std::function<bool(int, int)> loop_factors = [](int n, int f) -> bool {
  return f > std::sqrt(static_cast<double>(n)) ? true: n % f == 0 ? false: loop_factors(n, f += 2);
};

//=============================================================================
std::function<bool(int)> is_prime = [](int n) -> bool {
  return n == 1 ? false : n % 2 == 0 ? n == 2 : loop_factors(n, 3);
};

//=============================================================================
TEST(OneLineIsPrimeLambda, lambda)
{
  std::cout << std::boolalpha;
  for (int i = 2; i < 20; ++i) {
    std::cout << i << ": " << is_prime(i) << "\n";
  }
  TEST_FALSE(is_prime(1));
  TEST_TRUE(is_prime(2));
  TEST_TRUE(is_prime(3));
  TEST_FALSE(is_prime(4));
  TEST_TRUE(is_prime(5));
  TEST_FALSE(is_prime(6));
  TEST_TRUE(is_prime(7));
  TEST_FALSE(is_prime(8));
  TEST_FALSE(is_prime(9));
  TEST_FALSE(is_prime(10));
  TEST_TRUE(is_prime(11));
  TEST_FALSE(is_prime(12));
  TEST_TRUE(is_prime(13));
  TEST_FALSE(is_prime(14));
  TEST_FALSE(is_prime(15));
  TEST_FALSE(is_prime(16));
  TEST_TRUE(is_prime(17));
  TEST_FALSE(is_prime(18));
  TEST_TRUE(is_prime(19));
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
