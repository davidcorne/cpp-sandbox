//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_VARIADIC_TEMPLATES
#include <vector>

#include <UnitCpp/Test.h>

#include "Enumeration.h"
#include "enumerate.h"
#include "Printer.h"

//=============================================================================
TEST(Enumeration, vector)
{
  // This uses the Enumeration class, this makes no copies of the array.
  std::vector<double> array = {0, 2, 4, 6, 8};
  int i = 0;
  for (std::pair<int, double> pair: Enumeration<std::vector<double> >(array)) {
    TEST_EQUAL(pair.first, i, "Wrong index.");
    TEST_EQUAL(pair.second, static_cast<double>(i * 2), "Wrong value.");
    ++i;
  }
  TEST_EQUAL(i, 5, "Should iterate 5 times.");

  Printer printer(std::cout);
  printer.print("\nExample use.\n");
  for (std::pair<int, double> pair: Enumeration<std::vector<double> >(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

  printer.print("\nUsing make_enumeration()\n");
  for (std::pair<int, double> pair: make_enumeration(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

}

//=============================================================================
TEST(Enumeration, enumerate)
{
  // Uses the free funtion enumerate. The disadvantage to this is that it
  // creates and copies an extra container.
  std::vector<double> array = {0, 2, 4, 6, 8};
  int i = 0;
  for (std::pair<int, double> pair: enumerate(array)) {
    TEST_EQUAL(pair.first, i, "Wrong index.");
    TEST_EQUAL(pair.second, static_cast<double>(i * 2), "Wrong value.");
    ++i;
  }
  TEST_EQUAL(i, 5, "Should iterate 5 times.");

  Printer printer(std::cout);
  printer.print("\nExample use.\n");
  for (std::pair<int, double> pair: enumerate(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

}
//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN;
#endif

