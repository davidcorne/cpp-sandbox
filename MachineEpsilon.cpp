//=============================================================================
//
// A test added by me, but the implementation is from:
// http://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C.2B.2B
//

#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <limits>

#include "UnitTest.h"

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
class utest_MachineEpsilon : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_float_eps();
    test_double_eps();
  }

private:

  void test_float_eps();
  void test_double_eps();

};

//=============================================================================
void utest_MachineEpsilon::test_float_eps()
{
  print(DGC_CURRENT_FUNCTION);
  float eps = machine_eps<float, uint32_t>();
  test(std::numeric_limits<float>::epsilon() == eps, "Wrong calculated eps.");

}

//=============================================================================
void utest_MachineEpsilon::test_double_eps()
{
  print(DGC_CURRENT_FUNCTION);
  float eps = machine_eps<double, uint64_t>();
  test(std::numeric_limits<double>::epsilon() == eps, "Wrong calculated eps.");
}

//=============================================================================
int main() {
  utest_MachineEpsilon test;
  test.run_tests();
  return 0;
}
