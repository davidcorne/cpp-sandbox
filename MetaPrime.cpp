//=============================================================================
// Trying to find primality at compile time.

#include "Capabilities.h"
#ifdef CAPABILITY_CONSTEXPR

#include <UnitCpp.h>

#include "MetaDivides.h"
#include "TML.h"

//=============================================================================
template <unsigned int X, unsigned int Y>
struct RecursivelyDivides {
  constexpr static const bool result =
    If<Divides<Y, X>::result, true, RecursivelyDivides<X, Y - 1>::result>::result;
};

//=============================================================================
template <unsigned int X>
struct RecursivelyDivides<X, 1> {
  constexpr static const bool result = false;
};

//=============================================================================
template <unsigned int X>
struct IsPrime {
  constexpr static const bool result = !RecursivelyDivides<X, X / 2>::result;
};

//=============================================================================
template <>
struct IsPrime<0> {
  constexpr static const bool result = false;
};

//=============================================================================
template <>
struct IsPrime<1> {
  constexpr static const bool result = false;
};

//=============================================================================
// Declare the constexpr symbols
template <unsigned int X, unsigned int Y>
constexpr const bool RecursivelyDivides<X, Y>::result;

template <unsigned int X>
constexpr const bool IsPrime<X>::result;
constexpr const bool IsPrime<0>::result;
constexpr const bool IsPrime<1>::result;

//=============================================================================
TEST(IsPrime, one)
{
  TEST_FALSE(IsPrime<1>::result);
}

//=============================================================================
TEST(IsPrime, zero)
{
  TEST_FALSE(IsPrime<0>::result);
}

//=============================================================================
TEST(IsPrime, primes)
{
  TEST_TRUE(IsPrime<2>::result);
  TEST_TRUE(IsPrime<3>::result);
  TEST_TRUE(IsPrime<5>::result);
  TEST_TRUE(IsPrime<7>::result);
  TEST_TRUE(IsPrime<11>::result);
  TEST_TRUE(IsPrime<13>::result);
  TEST_TRUE(IsPrime<17>::result);
  TEST_TRUE(IsPrime<19>::result);
  TEST_TRUE(IsPrime<23>::result);
  TEST_TRUE(IsPrime<29>::result);
  TEST_TRUE(IsPrime<31>::result);
  TEST_TRUE(IsPrime<37>::result);
  TEST_TRUE(IsPrime<41>::result);
  TEST_TRUE(IsPrime<43>::result);
  TEST_TRUE(IsPrime<47>::result);
  TEST_TRUE(IsPrime<53>::result);
  TEST_TRUE(IsPrime<59>::result);
  TEST_TRUE(IsPrime<61>::result);
  TEST_TRUE(IsPrime<67>::result);
  TEST_TRUE(IsPrime<71>::result);
  TEST_TRUE(IsPrime<73>::result);
  TEST_TRUE(IsPrime<79>::result);
  TEST_TRUE(IsPrime<83>::result);
  TEST_TRUE(IsPrime<89>::result);
  TEST_TRUE(IsPrime<97>::result);
}

//=============================================================================
TEST(IsPrime, non_primes)
{
  TEST_FALSE(IsPrime<4>::result);
  TEST_FALSE(IsPrime<6>::result);
  TEST_FALSE(IsPrime<8>::result);
  TEST_FALSE(IsPrime<9>::result);
  TEST_FALSE(IsPrime<10>::result);
  TEST_FALSE(IsPrime<12>::result);
  TEST_FALSE(IsPrime<14>::result);
  TEST_FALSE(IsPrime<15>::result);
  TEST_FALSE(IsPrime<16>::result);
  TEST_FALSE(IsPrime<18>::result);
  TEST_FALSE(IsPrime<20>::result);
  TEST_FALSE(IsPrime<21>::result);
  TEST_FALSE(IsPrime<22>::result);
  TEST_FALSE(IsPrime<24>::result);
  TEST_FALSE(IsPrime<25>::result);
  TEST_FALSE(IsPrime<26>::result);
  TEST_FALSE(IsPrime<27>::result);
  TEST_FALSE(IsPrime<28>::result);
  TEST_FALSE(IsPrime<30>::result);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}


#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
