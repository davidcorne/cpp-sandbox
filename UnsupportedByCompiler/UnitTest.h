//=============================================================================
// Unit test class.

#ifndef UnitTest_H
#define UnitTest_H

#include <string>
#include <assert.h>

#include "../CurrentFunction.h"

//============================================================================
class UnitTest {
public:
  
  UnitTest();
  ~UnitTest();
  
  virtual void run_tests() = 0;

protected:

  void test(bool pass, std::string message);
  
  void print(std::string message);

};

//=============================================================================
UnitTest::UnitTest()
{
}

//=============================================================================
UnitTest::~UnitTest()
{
}

//=============================================================================
void UnitTest::test(bool pass, std::string message)
{
  if (pass) {
    std::cout << "Pass: " << message << std::endl;
  } else {
    std::cout << "Fail: " << message << std::endl;
    assert(false);
  }
}

//=============================================================================
void UnitTest::print(std::string message)
{
  std::string banner(
    "\n========================================"
    "=======================================\n"
  );
  std::cout << banner << message << banner << std::endl;
}

#endif
