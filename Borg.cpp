//=============================================================================
//
//D Inspired by
//D http://code.activestate.com/recipes/66531-singleton-we-dont-need-no-stinkin-singleton-the-bo/
//

#include <iostream>
#include <UnitCpp.h>

//=============================================================================
class IntBorg {
public:

  IntBorg();

  void set_i(int i);
  int i() const;
  
private:
  static int s_i;
};

//=============================================================================
TEST(IntBorg, int)
{
  IntBorg b_1;
  b_1.set_i(10);
  IntBorg b_2;
  TEST_EQUAL(b_2.i(), 10);
  b_1.set_i(15);
  TEST_EQUAL(b_2.i(), 15);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

int IntBorg::s_i(0);

//=============================================================================
IntBorg::IntBorg()
{
}

//=============================================================================
void IntBorg::set_i(int i)
{
  s_i = i;
}

//=============================================================================
int IntBorg::i() const
{
  return s_i;
}
