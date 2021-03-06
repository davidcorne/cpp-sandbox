//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef CAPABILITY_VARIADIC_TEMPLATES
#include <sstream>

#include <UnitCpp.h>

#include "Printer.h"

//=============================================================================
TEST(Printer, print)
{
  std::stringstream ss;
  Printer printer(ss);
  printer.print("hello");
  TEST_EQUAL(ss.str(), "hello\n", "Printed the correct thing.");
  ss.str("");
  printer.print(
    "This is a way of printing at least, ",
    50,
    " different types."
  );
  TEST_EQUAL(
    ss.str(),
    "This is a way of printing at least, 50 different types.\n",
    "Multiple types in one."
  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES)
#endif
