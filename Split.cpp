//=============================================================================
//
// 

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <UnitCpp/Test.h>

//=============================================================================
std::vector<std::string> split(std::string in, char delimiter=' ')
{
  std::vector<std::string> out;
  std::stringstream string_stream(in);
  std::string item;
  while (getline(string_stream, item, delimiter)) {
    out.push_back(item);
  }
  return out;
}

//=============================================================================
TEST(Split, other_delimiters)
{
  std::vector<std::string> out(split("Name,Address,Phone Number", ','));
  TEST_EQUAL(out.size(), 3, "Wrong size for out.");
  TEST_EQUAL(out[0], "Name", "Wrong element 0 in out.");
  TEST_EQUAL(out[1], "Address", "Wrong element 1 in out.");
  TEST_EQUAL(out[2], "Phone Number", "Wrong element 2 in out.");
  
}

//=============================================================================
TEST(Split, space)
{
  std::vector<std::string> out(split("This is a sentence."));
  TEST_EQUAL(out.size(), 4, "Wrong size for out.");
  TEST_EQUAL(out[0], "This", "Wrong element 0 in out.");
  TEST_EQUAL(out[1], "is", "Wrong element 1 in out.");
  TEST_EQUAL(out[2], "a", "Wrong element 2 in out.");
  TEST_EQUAL(out[3], "sentence.", "Wrong element 3 in out.");

}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
