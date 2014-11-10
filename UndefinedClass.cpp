//=============================================================================
//
// 

#include <iostream>

#include <UnitCpp/Test.h>

//=============================================================================
class UndefinedClass;

//=============================================================================
TEST(UndefinedClass, pointer)
{
  UndefinedClass* undef = 0;
  TEST_FALSE(undef, "undef should be null");
  undef = reinterpret_cast<UndefinedClass*>(new int);
  TEST_TRUE(undef, "undef shoulf not be null.");
}

//=============================================================================
TEST(UndefinedClass, reference)
{
  UndefinedClass& undef = *reinterpret_cast<UndefinedClass*>(new int);
  TEST_TRUE(&undef, "undef is not null.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
