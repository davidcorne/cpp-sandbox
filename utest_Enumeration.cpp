//=============================================================================
//
// 

#include "Capabilities.h"
#if defined(CAPABILITY_VARIADIC_TEMPLATES) && defined(CAPABILITY_USER_DEFINED_LITERALS) && defined(CAPABILITY_CONSTEXPR)

#define LOSS_OF_DATA_CONVERSION 1
#include "IgnoreDiagnostics.h"

#include <vector>

#include <UnitCpp.h>

#include "Enumeration.h"
#include "enumerate.h"
#include "Printer.h"
#include "size_t_literal.h"

//=============================================================================
TEST(Enumeration, vector)
{
  // This uses the Enumeration class, this makes no copies of the array.
  std::vector<double> array = {0, 2, 4, 6, 8};
  size_t i = 0;
  for (std::pair<size_t, double> pair: Enumeration<std::vector<double> >(array)) {
    TEST_EQUAL(pair.first, i, "Wrong index.");
    TEST_EQUAL(pair.second, static_cast<double>(i * 2), "Wrong value.");
    ++i;
  }
  TEST_EQUAL(i, 5_st, "Should iterate 5 times.");

  Printer printer(std::cout);
  printer.print("\nExample use.\n");
  for (std::pair<size_t, double> pair: Enumeration<std::vector<double> >(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

  printer.print("\nUsing make_enumeration()\n");
  for (std::pair<size_t, double> pair: make_enumeration(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

}

//=============================================================================
TEST(Enumeration, enumerate)
{
  // Uses the free funtion enumerate. The disadvantage to this is that it
  // creates and copies an extra container.
  std::vector<double> array = {0, 2, 4, 6, 8};
  size_t i = 0;
  for (std::pair<size_t, double> pair: enumerate(array)) {
    TEST_EQUAL(pair.first, i, "Wrong index.");
    TEST_EQUAL(pair.second, static_cast<double>(i * 2), "Wrong value.");
    ++i;
  }
  TEST_EQUAL(i, 5_st, "Should iterate 5 times.");

  Printer printer(std::cout);
  printer.print("\nExample use.\n");
  for (std::pair<size_t, double> pair: enumerate(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

}
//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES)
#endif

