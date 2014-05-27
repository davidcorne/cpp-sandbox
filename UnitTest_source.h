//=============================================================================
#include <assert.h>
#include <iostream>

//=============================================================================
UnitTest::UnitTest()
  : m_printer(std::cout)
{
}

//=============================================================================
void UnitTest::test(bool pass, std::string message)
{
  if (pass) {
    message = "Pass: " + message;
  } else {
    message = "Fail: " + message;
  }
  std::cout << message << std::endl;
  assert(pass);
}

//=============================================================================
template <typename T, typename... Args>
void UnitTest::print(const T& message, Args... arguments)
{
  m_printer.print(message, arguments...);
}
  
