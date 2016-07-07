//=============================================================================
//

#include "to_string.h"
#include "to_string.h"

#include <UnitCpp.h>

//=============================================================================
TEST(to_string, impl)
{
  {
    int value = 56;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "56", "Should convert an int correctly.");
  }
  {
    long value = 6389;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "6389", "Should convert a long correctly.");
  }
  {
    long long value = -123456;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "-123456", "Should convert a long long correctly.");
  }
  {
    unsigned value = 123;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "123", "Should convert an unsigned correctly.");
  }
  {
    unsigned long value = 45678;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "45678", "Should convert an unsigned long correctly.");
  }
  {
    unsigned long long value = 987;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "987", "Should convert an unsigned long long correctly.");
  }
  {
    float value = 3.14f;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "3.14", "Should convert a float correctly.");
  }
  {
    double value = 2.72;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, std::string("2.72"), "Should convert a double correctly.");
  }
  {
    long double value = 123.123;
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "123.123", "Should convert a long double correctly.");
  }
  {
    std::string value = "Hello, World!";
    std::string s = dgc::to_string(value);
    TEST_EQUAL(s, "Hello, World!", "Should convert a std::string correctly.");
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
