//=============================================================================
#include <assert.h>
#include <iostream>

//=============================================================================
UnitTest::UnitTest()
  : m_printer(std::cout)
{
}

//=============================================================================
template <typename... Args>
void UnitTest::test(bool pass, Args... arguments)
{
  std::string message("");
  if (pass) {
    message += "Pass: ";
  } else {
    message += "Fail: ";
  }
  std::cout << message;
  m_printer.print(arguments...);
  assert(pass);
}

//=============================================================================
template <typename T, typename... Args>
void UnitTest::print(const T& message, Args... arguments)
{
  static std::string banner(
    "======================================"
    "======================================="
  );
  m_printer.print("\n" + banner);
  m_printer.print(message, arguments...);
  m_printer.print(banner + "\n");
}
  
