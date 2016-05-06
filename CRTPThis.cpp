//=============================================================================
// Test that you can use the *this in the curiously recurring template pattern

#include <UnitCpp.h>

//=============================================================================
template <typename tDERIVED>
struct Selfable {

  tDERIVED& self() {
    return *reinterpret_cast<tDERIVED*>(this);
  }
  
};

//=============================================================================
struct MyInt : public Selfable<MyInt> {

  MyInt(int a_i) : i(a_i) {}

  int i;
};

//=============================================================================
TEST(MyInt, self)
{
  MyInt an_int(5);
  TEST_EQUAL(an_int.self().i, 5);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
