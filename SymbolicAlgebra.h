//=============================================================================
//
// A header for doing mathematical calculations. We're going to stick to
// polynomials.

#ifndef SymbolicAlgebra_H
#define SymbolicAlgebra_H

#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

#include <cmath>
#include <cassert>

//=============================================================================
class Term {
public:

  Term(double coefficient, int exponent);

  double coefficient() const;

  int exponent() const;
  
private:

  double m_coefficient;
  int m_exponent;
};

//=============================================================================
class PolynomialExpression {
public:

  PolynomialExpression(std::initializer_list<Term> initializer);

  std::ostream& out(std::ostream& os, char variable) const;

  int order() const;

  double coefficient(int order) const;
  
private:

  bool has(int order) const;
  // Has a term of "order".
  
  const Term& at(int order) const;
  // Get the term of "order".

  std::vector<Term>::const_iterator find(int order) const;
  // Find a term of given order.
  
  struct TermOrdinality {
    bool operator()(const Term& a, const Term& b) const {
      return a.exponent() > b.exponent();
    }
  };
  std::vector<Term> m_terms;
};

//=============================================================================
class Root {
public:

  Root(std::complex<double> solution);
  
  std::complex<double> solution() const;
  
private:

  std::complex<double> m_solution;
};

//=============================================================================
class PolynomialExpressionSolver {
public:

  std::vector<Root> solve(const PolynomialExpression& expression) const;
  
private:

  std::vector<Root> solve_quadratic(
    const PolynomialExpression& expression
  ) const;
  
  std::vector<Root> solve_linear(
    const PolynomialExpression& expression
  ) const;
  
};

//=============================================================================
std::ostream& operator<<(std::ostream& os, const PolynomialExpression& expression)
{
  return expression.out(os, 'x');
}

//=============================================================================
Term::Term(double coefficient, int exponent)
  : m_coefficient(coefficient),
    m_exponent(exponent)
{
}

//=============================================================================
double Term::coefficient() const
{
  return m_coefficient;
}

//=============================================================================
int Term::exponent() const
{
  return m_exponent;
}

//=============================================================================
PolynomialExpression::PolynomialExpression(std::initializer_list<Term> initializer)
  : m_terms(initializer)
{
  std::sort(begin(m_terms), end(m_terms), TermOrdinality());
}

//=============================================================================
int PolynomialExpression::order() const
{
  int l_order = 0;
  if (!m_terms.empty()) {
    l_order = m_terms.front().exponent();
  }
  return l_order;
}

//=============================================================================
double PolynomialExpression::coefficient(int order) const
{
  auto it = find(order);
  return it != end(m_terms) ? it->coefficient() : 0;
}
  
//=============================================================================
bool PolynomialExpression::has(int order) const
// Has a term of "order".
{
  return find(order) != end(m_terms);
}
  
//=============================================================================
const Term& PolynomialExpression::at(int order) const
// Get the term of "order".
{
  assert(has(order) && "Can't get a term with given order.");
  return *find(order);
}

//=============================================================================
std::vector<Term>::const_iterator PolynomialExpression::find(int order) const
{
  return std::find_if(
    begin(m_terms),
    end(m_terms),
    [order](const Term& term)->bool{return term.exponent() == order;}
  );
}

//=============================================================================
std::ostream& PolynomialExpression::out(std::ostream& os, char variable) const
{
  for (auto it = begin(m_terms); it != end(m_terms); ++it) {
    const Term& term = *it;
    double coefficient = term.coefficient();
    int exponent = term.exponent();
    if (coefficient != 0) {
      char sign = coefficient < 0 ? '-' : '+';
      coefficient = std::abs(coefficient);
      if (it != begin(m_terms)) {
        os << sign << ' ';
      } else if (sign == '-') {
        os << sign;
      }
      if (coefficient != 1 || exponent == 0) {
        os << coefficient;
      }
      if (exponent != 0) {
        os << variable;
        if (exponent != 1) {
          os << "^" << exponent;
        }
      }
    }
    if ((it + 1) != end(m_terms)) {
      os << " ";
    }
  }
  return os;
}


//=============================================================================
Root::Root(std::complex<double> solution)
  : m_solution(solution)
{
}

//=============================================================================
std::complex<double> Root::solution() const
{
  return m_solution;
}

//=============================================================================
std::vector<Root> PolynomialExpressionSolver::solve(
  const PolynomialExpression& expression
) const
{
  int order = expression.order();
  std::vector<Root> roots;
  if (order == 1) {
    roots = solve_linear(expression);
  } else if (order == 2) {
    roots = solve_quadratic(expression);
  }
  return roots;
}


//=============================================================================
std::vector<Root> PolynomialExpressionSolver::solve_quadratic(
  const PolynomialExpression& expression
) const
{
  assert(expression.order() == 2 && "Should be order 2");
  double a = expression.coefficient(2);
  double b = expression.coefficient(1);
  double c = expression.coefficient(0);
  // (-b +- sqrt(b^2 - 4ac)) / 2a
  double determinant = (b*b) - (4*a*c);
  std::vector<Root> roots;
  if (determinant < 0) {
    // deal with complex roots
  } else if (determinant == 0) {
    roots.push_back(Root(std::complex<double>((-1 * b) / (2 * a))));
  } else {
    roots.push_back(
      Root(std::complex<double>(((-1 * b) + std::sqrt(determinant)) / (2 * a)))
    );
    roots.push_back(
      Root(std::complex<double>(((-1 * b) - std::sqrt(determinant)) / (2 * a)))
    );
  }
  
  return roots;
}

//=============================================================================
std::vector<Root> PolynomialExpressionSolver::solve_linear(
  const PolynomialExpression& expression
) const
{
  assert(expression.order() == 1 && "Should be order 1");
  std::vector<Root> roots;
  // ax + b = 0
  // x = -b/a
  double a = expression.coefficient(1);
  double b = expression.coefficient(0);
  if (a != 0) {
    roots.push_back(Root((-1 * b) / a));
  }
  return roots;
}

#endif
