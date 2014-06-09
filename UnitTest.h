//=============================================================================
// Unit test class.

#ifndef UnitTest_H
#define UnitTest_H

#include <string>

#include "Printer.h"
#include "CurrentFunction.h"

//============================================================================
class UnitTest {
public:
  
  UnitTest();

  virtual void run_tests() = 0;

protected:

  template <typename... Args>
  void test(bool pass, Args... arguments);
  
  template <typename T, typename... Args>
  void print(const T& message, Args... arguments);

private:

  Printer m_printer;
};

#include "UnitTest_source.h"

#endif
