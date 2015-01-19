#include <UnitCpp.h>

#include "StringOperations.h"

//=============================================================================
TEST(StringOperations, join)
{
  std::vector<std::string> array;
  std::string result = join(begin(array), end(array), ':');
  TEST_EQUAL(result, std::string(""));
  
  array.push_back("hi");
  result = join(begin(array), end(array), '\n');
  TEST_EQUAL(result, std::string("hi"));
  
  array.push_back("there");
  result = join(begin(array), end(array), ' ');
  TEST_EQUAL(result, std::string("hi there"));
}

//=============================================================================
TEST(StringOperations, split)
{
  std::vector<std::string> result;
  std::string source("This is a test:isn't it.");
  split(source, '\n', back_inserter(result));
  TEST_EQUAL(result.size(), 1);
  TEST_EQUAL(result[0], source);
  result.clear();

  split(source, ' ', back_inserter(result));
  TEST_EQUAL(result.size(), 5);
  TEST_EQUAL(result[0], std::string("This"));
  TEST_EQUAL(result[1], std::string("is"));
  TEST_EQUAL(result[2], std::string("a"));
  TEST_EQUAL(result[3], std::string("test:isn't"));
  TEST_EQUAL(result[4], std::string("it."));
  result.clear();

  split(source, 'i', back_inserter(result));
  TEST_EQUAL(result.size(), 5);
  TEST_EQUAL(result[0], std::string("Th"));
  TEST_EQUAL(result[1], std::string("s "));
  TEST_EQUAL(result[2], std::string("s a test:"));
  TEST_EQUAL(result[3], std::string("sn't "));
  TEST_EQUAL(result[4], std::string("t."));
  result.clear();
  
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
