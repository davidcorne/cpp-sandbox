//=============================================================================
//

#include <sstream>
#include <UnitCpp.h>

#include "PrintableType.h"

//=============================================================================
TEST(PrintableType, primitives)
{
  std::stringstream ss;
  print(5, ss);
  TEST_EQUAL(ss.str(), "5\n");
  ss.str("");

  print(-2.9, ss);
  TEST_EQUAL(ss.str(), "-2.9\n");
  ss.str("");

  print(true, ss);
  TEST_EQUAL(ss.str(), "1\n");
  ss.str("");

  print(false, ss);
  TEST_EQUAL(ss.str(), "0\n");
  ss.str("");

  ss << std::boolalpha;
  print(false, ss);
  TEST_EQUAL(ss.str(), "false\n");
  ss.str("");
  
}

//=============================================================================
enum Greeting {
  Hi,
  Hello,
  Salut
};

//=============================================================================
TEST(PrintableType, enum)
{
  std::stringstream ss;
  print(Hi, ss);
  TEST_EQUAL(ss.str(), "0\n");
  ss.str("");

  print(Hello, ss);
  TEST_EQUAL(ss.str(), "1\n");
  ss.str("");
}

struct NotPrintable {

};

//=============================================================================
TEST(PrintableType, NotPrintable)
{
  std::stringstream ss;
  NotPrintable not_printable;
  print(not_printable, ss);
  size_t position = ss.str().find(typeid(NotPrintable).name());
  TEST_NOT_EQUAL(position, std::string::npos);
  ss.str("");
}

struct Printable {

};

std::ostream& operator<<(std::ostream& os, const Printable&)
{
  return os;
}

//=============================================================================
TEST(PrintableType, Printable)
{
  std::stringstream ss;
  Printable printable;
  print(printable, ss);
  TEST_EQUAL(ss.str(), "\n");
  ss.str("");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

