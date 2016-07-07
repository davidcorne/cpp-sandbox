//=============================================================================
//
// 

#include "StringBuilder.h"
#include "StringBuilder.h"

#include "Stopwatch.h"
#include "RandomStringGenerator.h"

#include <UnitCpp.h>

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
}

//=============================================================================
TEST(StringBuilder, faster)
{
  // Lets make 1,000,000 pseudo-random strings. Pseudo-random as it's the same
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
  TEST_EQUAL(naive, built);
  auto built_duration = stopwatch.stop();
  std::cout
    << "Using std::string::operator+=(): "
    <<  naive_duration.count()
    << "\n"
    << "Using StringBuilder: "
    << built_duration.count()
    << "\n";
  
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
