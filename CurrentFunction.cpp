//=============================================================================
//
// 

#include <UnitCpp.h>

#include "CurrentFunction.h"

//=============================================================================
std::string function_name()
{
  return std::string(DGC_CURRENT_FUNCTION);
}

//=============================================================================
TEST(CurrentFunction, name)
{
  std::string name(function_name());
  auto index = name.find("function_name(");
  std::cout << name << std::endl;
  TEST_NOT_EQUAL(index, std::string::npos);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
