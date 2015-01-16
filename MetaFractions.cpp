//=============================================================================
//
// These are template meta-programming fractions. They are inspired by this
// http://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming/

#include "Capabilities.h"

#ifdef CAPABILITY_CONSTEXPR
#include <UnitCpp.h>

#include "GCD.h"

//=============================================================================
template <int tNUMERATOR, int tDENOMINATOR>
struct Fraction {
private:
  static const int gcd = GCD<tNUMERATOR, tDENOMINATOR>::result;
public:
  constexpr static const int Numerator = tNUMERATOR / gcd;
  constexpr static const int Denominator = tDENOMINATOR / gcd;
};

template <int tNUMERATOR, int tDENOMINATOR>
constexpr const int Fraction<tNUMERATOR, tDENOMINATOR>::Numerator;

template <int tNUMERATOR, int tDENOMINATOR>
constexpr const int Fraction<tNUMERATOR, tDENOMINATOR>::Denominator;

//=============================================================================
template <int tSCALAR, typename tFRACTION>
struct ScalarMultiplication {
  typedef
    Fraction<tSCALAR * tFRACTION::Numerator, tFRACTION::Denominator>
    result;
};

//=============================================================================
template <typename tFRACTION_1, typename tFRACTION_2>
struct FractionMultiplication {
  typedef
    Fraction<
      tFRACTION_1::Numerator * tFRACTION_2::Numerator,
      tFRACTION_1::Denominator * tFRACTION_2::Denominator
    >
    result;
};

//=============================================================================
TEST(MetaFractions, dimensions)
{
  TEST_EQUAL((Fraction<1, 2>::Numerator), 1);
  TEST_EQUAL((Fraction<1, 4>::Denominator), 4);

  typedef Fraction<3, 4> ThreeQuarters;
  TEST_EQUAL(ThreeQuarters::Numerator, 3);
  TEST_EQUAL(ThreeQuarters::Denominator, 4);

  typedef Fraction<2, 4> TwoQuarters;
  TEST_EQUAL(TwoQuarters::Numerator, 1);
  TEST_EQUAL(TwoQuarters::Denominator, 2);
}

//=============================================================================
TEST(MetaFractions, scalar_multiplication)
{
  typedef ScalarMultiplication<3, Fraction<1, 4> >::result ThreeQuarters;
  TEST_EQUAL(ThreeQuarters::Numerator, 3);
  TEST_EQUAL(ThreeQuarters::Denominator, 4);

  typedef ScalarMultiplication<2, Fraction<1, 4> >::result OneHalf;
  TEST_EQUAL(OneHalf::Numerator, 1);
  TEST_EQUAL(OneHalf::Denominator, 2);
}

//=============================================================================
TEST(MetaFractions, fraction_multiplication)
{
  typedef Fraction<1, 2> OneHalf;
  typedef Fraction<1, 4> OneQuarter;
  typedef FractionMultiplication<OneHalf, OneQuarter>::result OneEighth;
  TEST_EQUAL(OneEighth::Numerator, 1);
  TEST_EQUAL(OneEighth::Denominator, 8);

  typedef Fraction<2, 3> TwoThirds;
  typedef FractionMultiplication<OneHalf, TwoThirds>::result OneThird;
  TEST_EQUAL(OneThird::Numerator, 1);
  TEST_EQUAL(OneThird::Denominator, 3);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
