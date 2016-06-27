//=============================================================================
//
// 

#include "SymbolicAlgebra.h"
#include "SymbolicAlgebra.h"

#include <set>

#include <UnitCpp.h>

//=============================================================================
TEST(SymbolicAlgebra, print)
{
  PolynomialExpression expression{Term(1, 2), Term(2, 1), Term(1, 0)};
  std::stringstream ss;
  ss << expression;
  TEST_EQUAL(ss.str(), "x^2 + 2x + 1");
  
  ss.str("");
  expression.out(ss, 'y');
  TEST_EQUAL(ss.str(), "y^2 + 2y + 1");

  ss.str("");
  expression = PolynomialExpression{Term(-1, 2), Term(2, 1), Term(-1, 0)};
  expression.out(ss, 'z');
  TEST_EQUAL(ss.str(), "-z^2 + 2z - 1");
  
}

//=============================================================================
TEST(SymbolicAlgebra, getter)
{
  PolynomialExpression expression(
    {Term(1, 1), Term(2, 2), Term(3, 3), Term(4, 4), Term(5, 5)}
  );
  TEST_EQUAL(expression.coefficient(0), 0);
  TEST_EQUAL(expression.coefficient(1), 1);
  TEST_EQUAL(expression.coefficient(2), 2);
  TEST_EQUAL(expression.coefficient(3), 3);
  TEST_EQUAL(expression.coefficient(4), 4);
  TEST_EQUAL(expression.coefficient(5), 5);
  TEST_EQUAL(expression.coefficient(6), 0);
  TEST_EQUAL(expression.coefficient(7), 0);
  TEST_EQUAL(expression.coefficient(8), 0);
  TEST_EQUAL(expression.coefficient(9), 0);
  TEST_EQUAL(expression.coefficient(10), 0);
}

//=============================================================================
TEST(SymbolicAlgebra, order)
{
  {
    PolynomialExpression expression{};
    TEST_EQUAL(expression.order(), 0);
  }
  {
    PolynomialExpression expression{Term(5, 1)};
    TEST_EQUAL(expression.order(), 1);
  }
  {
    PolynomialExpression expression{Term(4, 1), Term(3, 2)};
    TEST_EQUAL(expression.order(), 2);
  }
  {
    PolynomialExpression expression{Term(4, 3)};
    TEST_EQUAL(expression.order(), 3);
  }
}
//=============================================================================
TEST(SymbolicAlgebra, solve)
{
  {
    // x - 4
    // roots: 4
    PolynomialExpression expression({Term(1, 1), Term(-4, 0)});
    std::vector<Root> roots = PolynomialExpressionSolver().solve(expression);
    TEST_EQUAL(roots.size(), 1u);
    TEST_EQUAL(roots.front().solution(), std::complex<double>(4));
  }
  {
    // 2x + 9
    // roots: -4.5
    PolynomialExpression expression({Term(2, 1), Term(9, 0)});
    std::vector<Root> roots = PolynomialExpressionSolver().solve(expression);
    TEST_EQUAL(roots.size(), 1u);
    TEST_EQUAL(roots.front().solution(), std::complex<double>(-4.5));
  }
  {
    // x^2 - 1
    // roots: 1, -1
    PolynomialExpression expression({Term(1, 2), Term(-1, 0)});
    std::vector<Root> roots = PolynomialExpressionSolver().solve(expression);
    TEST_EQUAL(roots.size(), 2u);
    std::vector<std::complex<double>> root_set;
    for (const Root& root : roots) {
      root_set.push_back(root.solution());
    }
    TEST_NOT_EQUAL(
      std::find(begin(root_set), end(root_set), std::complex<double>(1)),
      end(root_set),
      "Should find 1 as a root."
    );
    TEST_NOT_EQUAL(
      std::find(begin(root_set), end(root_set), std::complex<double>(-1)),
      end(root_set),
      "Should find -1 as a root."
    );
  }
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
