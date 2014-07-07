//=============================================================================
//
// 

#include <vector>

#include "UnitTest.h"
#include "Enumeration.h"
#include "enumerate.h"

//=============================================================================
class utest_Enumeration : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_vector();
    test_enumerate();
  }

private:

  void test_vector();
  void test_enumerate();

};

//=============================================================================
void utest_Enumeration::test_vector()
{
  // This uses the Enumeration class, this makes no copies of the array.
  print(DGC_CURRENT_FUNCTION);
  std::vector<double> array = {0, 2, 4, 6, 8};
  int i = 0;
  for (std::pair<int, double> pair: Enumeration<std::vector<double> >(array)) {
    test(pair.first == i, "Wrong index.");
    test(pair.second == (double)(i * 2), "Wrong value.");
    ++i;
  }
  test(i == 5, "Should iterate 5 times.");

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
void utest_Enumeration::test_enumerate()
{
  // Uses the free funtion enumerate. The disadvantage to this is that it
  // creates and copies an extra container.
  print(DGC_CURRENT_FUNCTION);
  std::vector<double> array = {0, 2, 4, 6, 8};
  int i = 0;
  for (std::pair<int, double> pair: enumerate(array)) {
    test(pair.first == i, "Wrong index.");
    test(pair.second == (double)(i * 2), "Wrong value.");
    ++i;
  }
  test(i == 5, "Should iterate 5 times.");

  Printer printer(std::cout);
  printer.print("\nExample use.\n");
  for (std::pair<int, double> pair: enumerate(array)) {
    printer.print(pair.first, " x 2 = ", pair.second);
  }

}

//=============================================================================
int main() {
  utest_Enumeration test;
  test.run_tests();
  return 0;
}
