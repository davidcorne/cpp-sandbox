//=============================================================================
//
// 

#include "SymbolicAlgebra.h"
#include "SymbolicAlgebra.h"

#include <UnitCpp.h>


//=============================================================================
TEST(SymbolicAlgebra, print)
{
  Expression expression{Term(1, 2), Term(2, 1), Term(1, 0)};
  std::stringstream ss;
  ss << expression;
  TEST_EQUAL(ss.str(), "x^2 + 2x + 1");
  
  ss.str("");
  expression.out(ss, 'y');
  TEST_EQUAL(ss.str(), "y^2 + 2y + 1");

  ss.str("");
  expression = Expression{Term(-1, 2), Term(2, 1), Term(-1, 0)};
  expression.out(ss, 'z');
  TEST_EQUAL(ss.str(), "-z^2 + 2z - 1");
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
