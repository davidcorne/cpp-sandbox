#include <UnitCpp.h>

#include "RandomStringGenerator.h"
#include "RandomStringGenerator.h"

//=============================================================================
TEST(RandomStringGenerator, make_string)
{
  RandomStringGenerator generator;
  for (std::size_t i = 1u; i < 1000; ++i) {
    std::string generated = generator.make_string(i);
    std::cout << generated.length() << " " << i << "\n";
    TEST_LESS_THAN(generated.length(), i);
  }
}

//=============================================================================
TEST(RandomStringGenerator, make_strings)
{
  RandomStringGenerator generator;
  for (std::size_t length : std::vector<std::size_t>{10, 50, 500}) {
    std::vector<std::string> strings = generator.make_strings(length, 50);
    TEST_EQUAL(
      strings.size(),
      length,
      "Should have a vector of length strings."
    );
    for (const std::string& string : strings) {
      TEST_LESS_THAN(
        string.length(),
        std::size_t(50),
        "Should respect max_string_length"
      );
    }
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
