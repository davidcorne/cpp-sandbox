//=============================================================================
//
// 

#include "EnumConverter.h"
#include "EnumConverter.h"

#include <UnitCpp.h>

ENUM_WITH_CONVERTER(
  Day,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
);

//=============================================================================
TEST(Day, create)
{
  Day day = Monday;
  day = Tuesday;
  day = Wednesday;
  day = Thursday;
  day = Friday;
  day = Saturday;
  day = Sunday;
}

//=============================================================================
TEST(Day, convert)
{
  Day day = Monday;
  std::string day_string = DayConverter()(day);
  TEST_EQUAL(day_string, "Monday");
  day = Tuesday;
  day_string = DayConverter()(day);
  TEST_EQUAL(day_string, "Tuesday");
  day = Sunday;
  day_string = DayConverter()(day);
  TEST_EQUAL(day_string, "Sunday");
}

ENUM_WITH_CONVERTER(
  Greeting,
  Hello,
  Hi,
  Salut
);

//=============================================================================
TEST(Greeting, create)
{
  Greeting greeting = Hi;
  greeting = Hello;
  greeting = Salut;
}

//=============================================================================
TEST(Greeting, convert_to_string)
{
  GreetingConverter converter;

  Greeting greeting = Hi;
  std::string greeting_string = converter(greeting);
  TEST_EQUAL(greeting_string, "Hi");
  
  greeting = Hello;
  greeting_string = converter(greeting);
  TEST_EQUAL(greeting_string, "Hello");

  greeting = Salut;
  greeting_string = converter(greeting);
  TEST_EQUAL(greeting_string, "Salut");
}

//=============================================================================
TEST(Greeting, convert_from_string)
{
  GreetingConverter converter;

  std::string greeting_string("Hi");
  Greeting greeting = converter(greeting_string);
  TEST_EQUAL(greeting, Hi);
  
  greeting_string = std::string("Hello");
  greeting = converter(greeting_string);
  TEST_EQUAL(greeting, Hello);
  
  greeting_string = std::string("Salut");
  greeting = converter(greeting_string);
  TEST_EQUAL(greeting, Salut);
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
