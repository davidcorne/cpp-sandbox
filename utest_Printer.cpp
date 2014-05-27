//=============================================================================
//
// 

#include <sstream>

#include "UnitTest.h"
#include "Printer.h"

//=============================================================================
class utest_Printer : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_print();
  }

private:

  void test_print();

};

//=============================================================================
void utest_Printer::test_print()
{
  print(DGC_CURRENT_FUNCTION);
  std::stringstream ss;
  Printer printer(ss);
  printer.print("hello");
  test(ss.str() == "hello\n", "Printed the correct thing.");
  ss.str("");
  printer.print(
    "This is a way of printing at least, ",
    50,
    " different types."
  );
  test(
    ss.str() == "This is a way of printing at least, 50 different types.\n",
    "Multiple types in one."
  );
}

//=============================================================================
int main() {
  utest_Printer test;
  test.run_tests();
  return 0;
}

