//=============================================================================
//
// A header for doing mathematical calculations. We're going to stick to
// polynomials.

#ifndef SymbolicAlgebra_H
#define SymbolicAlgebra_H

#include <cmath>
#include <iostream>
#include <vector>

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
class Expression {
public:

  Expression(std::initializer_list<Term> initializer);

  std::ostream& out(std::ostream& os, char variable) const;
  
private:

  std::vector<Term> m_terms;
};

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Expression& expression)
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
Expression::Expression(std::initializer_list<Term> initializer)
  : m_terms(initializer)
{
}

//=============================================================================
std::ostream& Expression::out(std::ostream& os, char variable) const
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

#endif
