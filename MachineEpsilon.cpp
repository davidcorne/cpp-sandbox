//=============================================================================
//
// A test added by me, but the implementation is from:
// http://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C.2B.2B
//

#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <limits>

#include <UnitCpp/Test.h>

//=============================================================================
template<typename float_t, typename int_t>
float_t machine_eps()
{
  union
  {
    float_t f;
    int_t   i;
  } one, one_plus, little, last_little;
 
  one.f    = 1.0;
  little.f = 1.0;
  last_little.f = little.f;
 
  while(true)
  {
    one_plus.f = one.f;
    one_plus.f += little.f;
 
    if( one.i != one_plus.i )
    {
      last_little.f = little.f;
      little.f /= 2.0;
    }
    else
    {
      return last_little.f;
    }
  }
}

//=============================================================================
TEST(MachineEpsilon, float)
{
  float eps = machine_eps<float, uint32_t>();
  TEST_EQUAL(std::numeric_limits<float>::epsilon(), eps, "Wrong calculated eps.");

}

//=============================================================================
TEST(MachineEpsilon, double)
{
  float eps = machine_eps<double, uint64_t>();
  TEST_EQUAL(std::numeric_limits<double>::epsilon(), eps, "Wrong calculated eps.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
