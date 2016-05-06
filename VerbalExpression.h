//=============================================================================
//
// A class to make regex more intuitive, very much based on
// https://github.com/VerbalExpressions/JSVerbalExpressions

#ifndef VerbalExpression_H
#define VerbalExpression_H

#include "Capabilities.h"

#ifndef CAPABILITY_REGEX
#error "Can't include this without <regex>"
#endif

#include <numeric>
#include <regex>
#include <string>
#include <vector>

//=============================================================================
class VerbalExpression {
public:

  VerbalExpression& start_of_line();

  VerbalExpression& end_of_line();

  VerbalExpression& then(std::string expr);

  VerbalExpression& maybe(std::string expr);

  VerbalExpression& anything();

  VerbalExpression& anything_but(std::string expr);

  std::regex regex() const;

  std::string expression() const;
  
private:

  std::vector<std::string> m_accumulation;
};

//=============================================================================
VerbalExpression& VerbalExpression::start_of_line()
{
  m_accumulation.push_back("^");
  return *this;
}

//=============================================================================
VerbalExpression& VerbalExpression::end_of_line()
{
  m_accumulation.push_back("$");
  return *this;
}

//=============================================================================
VerbalExpression& VerbalExpression::then(std::string exp)
{
  m_accumulation.push_back(exp);
  return *this;
}

//=============================================================================
VerbalExpression& VerbalExpression::maybe(std::string exp)
{
  m_accumulation.push_back("(?:");
  m_accumulation.push_back(exp);
  m_accumulation.push_back(")?");
  return *this;
}

//=============================================================================
VerbalExpression& VerbalExpression::anything()
{
  m_accumulation.push_back(".*");
  return *this;
}

//=============================================================================
VerbalExpression& VerbalExpression::anything_but(std::string exp)
{
  m_accumulation.push_back("(?:[^");
  m_accumulation.push_back(exp);
  m_accumulation.push_back("]*)");
  return *this;
}

//=============================================================================
std::regex VerbalExpression::regex() const
{
  return std::regex(expression());
}

//=============================================================================
std::string VerbalExpression::expression() const
{
  std::string exp;
  for (const std::string& part : m_accumulation) {
    exp += part;
  }
  return exp;
}
  

#endif
