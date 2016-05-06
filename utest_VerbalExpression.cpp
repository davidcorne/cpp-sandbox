//=============================================================================
//
// 

#include "VerbalExpression.h"

#include <UnitCpp.h>


//=============================================================================
TEST(VerbalExpression, starts_with)
{
  // Testing starts with H
  std::vector<std::pair<std::string, bool>> results = {
    {"H", true},
    {" H", false},
    {"", false},
    {"h", false}
  };
  VerbalExpression vbex = VerbalExpression().start_of_line().then("H");
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }

  TEST_EQUAL(vbex.expression(), std::string("^H"));
}

//=============================================================================
TEST(VerbalExpression, maybe)
{
  std::vector<std::pair<std::string, bool>> results = {
    {"DdavidC", true},
    {"DC", true},
    {"anything else? DC", true},
    {"anything else? DdavidC", true},
    {"DdaviddavidC", false},
    {"D(david)C", false},
    {"DdaviC", false}
  };
  VerbalExpression vbex = VerbalExpression().then("D").maybe("david").then("C");
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }
}

//=============================================================================
TEST(VerbalExpression, anything)
{
  std::vector<std::pair<std::string, bool>> results = {
    {"DdavidC", true},
    {"DC", true},
    {"anything else? DC", true},
    {"anything else? DdavidC", true},
    {"DdaviddavidC", true},
    {"D(david)C", true},
    {"DdaviC", true},
    {"Ddavi", false},
    {"daviC", false},
    {"D", false},
    {"C", false}
  };
  VerbalExpression vbex = VerbalExpression().then("D").anything().then("C");
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }
}

//=============================================================================
TEST(VerbalExpression, anything_but)
{
  std::vector<std::pair<std::string, bool>> results = {
    {"DdavidC", false},
    {"DC", true},
    {"anything else? DC", true},
    {"anything else? DavidC", false},
    {"DdaviddavidC", false},
    {"D(david)C", false},
    {"DdaviC", false},
    {"DavidC", false},
    {"daviC", false},
    {"D", false},
    {"C", false}
  };
  VerbalExpression vbex =
    VerbalExpression().then("D").anything_but("avid").then("C");
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }
}

//=============================================================================
TEST(VerbalExpression, end_of_line)
{
  std::vector<std::pair<std::string, bool>> results = {
    {"d", false},
    {"C", true},
    {"anything else? DC", true},
    {"anything else? DavidC", true},
    {"DdaviddavidC", true},
    {"D(david)c", false},
    {"DdaviC", true},
    {"Davidc", false},
    {"daviC", true},
    {"D", true},
    {"C", true}
  };
  VerbalExpression vbex = VerbalExpression().then("[A-Z]").end_of_line();
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }
}

//=============================================================================
TEST(VerbalExpression, URL)
{

  std::vector<std::pair<std::string, bool>> results = {
    {"https://www.google.com", true},
    {"http://www.google.com", true},
    {"http:/www.google.com", false},
    {"htts://www.google.com", false},
    {"http://www.test.com/dir/filename.jpg?var1=foo#bar", true}
    
  };
  VerbalExpression vbex =
    VerbalExpression()
    .start_of_line()
    .then("http")
    .maybe("s")
    .then("://")
    .maybe("www.")
    .anything_but(" ")
    .end_of_line();
  
  std::regex regex = vbex.regex();
  for (auto result : results) {
    bool matched = std::regex_search(result.first, regex);
    TEST_EQUAL(matched, result.second);
  }
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
