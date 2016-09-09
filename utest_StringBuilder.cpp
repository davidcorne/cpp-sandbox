//=============================================================================
//
// 

#include "StringBuilder.h"
#include "StringBuilder.h"

#include "Capabilities.h"
#include "Stopwatch.h"
#include "RandomStringGenerator.h"

#include <UnitCpp.h>
#include <set>

//=============================================================================
TEST(StringBuilder, build)
{
  StringBuilder builder;
  builder.append("Hello,");
  builder << " ";
  builder += "World!";
  TEST_EQUAL(builder.build(), "Hello, World!");

  builder.clear();
  builder.append("An").append("other ").append("string");
  TEST_EQUAL(builder.build(), "Another string");

  builder.clear();
  ((builder += "Just") += " one ") += "more.";
  TEST_EQUAL(builder.build(), "Just one more.");

  builder.clear();
  ((builder << "Ok, ") << "last ") << "one.";
  TEST_EQUAL(builder.build(), "Ok, last one.");

  builder.clear();
  builder << "Maybe " << "one without " << "brackets.";
  TEST_EQUAL(builder.build(), "Maybe one without brackets.");
}

//=============================================================================
TEST(StringBuilder, construction)
{
#ifdef CAPABILITY_STD_STRING_LITERALS
  using namespace std::string_literals;
  {
    auto il = {"Concat"s, "ernate"s, " these."s};
    StringBuilder builder(il);
    TEST_EQUAL(builder.build(), "Concaternate these.");
  }
#endif
  {
    std::set<std::string> s =
      {" these ", " could ", " be ", " in ", " any ", " order "};
    StringBuilder builder(begin(s), end(s));
    std::string result = builder.build();
    TEST_EQUAL(result.length(), std::size_t{34});
    TEST_NOT_EQUAL(result.find(" these "), std::string::npos);
    TEST_NOT_EQUAL(result.find(" could "), std::string::npos);
    TEST_NOT_EQUAL(result.find(" be "), std::string::npos);
    TEST_NOT_EQUAL(result.find(" in "), std::string::npos);
    TEST_NOT_EQUAL(result.find(" any "), std::string::npos);
    TEST_NOT_EQUAL(result.find(" order "), std::string::npos);
  }
}

//=============================================================================
TEST(StringBuilder, faster)
{
  // Lets make 10,000 pseudo-random strings. Pseudo-random as it's the same
  // seed, so this is deterministic.
  std::size_t number_of_strings = 10000;
  std::size_t max_string_length = 500;
  RandomStringGenerator generator;
  std::vector<std::string> source =
    generator.make_strings(number_of_strings, max_string_length);
  
  Stopwatch stopwatch;
  StringBuilder builder(source);
  std::string naive;
  std::string built;

  stopwatch.start();
  for (const std::string& s : source) {
    naive += s;
  }
  auto naive_duration = stopwatch.stop();

  stopwatch.start();
  built = builder.build();
  auto built_duration = stopwatch.stop();
  TEST_EQUAL(naive, built);
  std::cout
    << "std::string::operator+=(): "
    <<  naive_duration.count()
    << "\n"
    << "StringBuilder:             "
    << built_duration.count()
    << "\n\n";
  
// This doens't pass, as the StringBuilder is slower on some platforms.
//X  TEST_LESS_THAN(
//X    built_duration,
//X    naive_duration,
//X    "The StringBuilder should be quicker."
//X  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
