//=============================================================================
//
// Are casts to void* implicit?

#include <UnitCpp.h>

//=============================================================================
struct Thing {

};

//=============================================================================
void do_thing(void*) {
  // Not actually much we can do with a void*.
}

//=============================================================================
TEST(VoidCast, test)
{
  Thing t;
  do_thing(&t);

  int i;
  do_thing(&i);

  do_thing(0);
  do_thing(nullptr);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
