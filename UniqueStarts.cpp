//=============================================================================
// Given a set of strings, this will return a map of those strings to the minimal strings
// which uniqueify them.
//
// e.g.
//
// unique_starts({"hi", "him", "hello"}) ->
// {{"hi", "hi"}, {"him", "him"}, {"hello", "he"}}

#include <map>
#include <set>
#include <string>

#include <UnitCpp.h>

//=============================================================================
std::map<std::string, std::string> unique_starts(
  const std::set<std::string>& strings
);

//=============================================================================
TEST(UniqueStarts, simple)
{
  auto map = unique_starts({"hi", "him", "hello"});
  TEST_EQUAL(map["hi"], "hi");
  TEST_EQUAL(map["him"], "him");
  TEST_EQUAL(map["hello"], "he");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
bool begins_with(const std::set<std::string>& set, std::string str)
{
  for (const std::string& match : set) {
    if (match.compare(0, str.length(), str) == 0) {
      return true;
    }
  }
  return false;
}

//=============================================================================
std::map<std::string, std::string> unique_starts(
  const std::set<std::string>& strings
)
{
  std::map<std::string, std::string> map;
  for (const std::string& str : strings) {
    map[str] = str;
  }
  for (auto& pair : map) {
    std::string str(pair.first);
    std::set<std::string> without(strings);
    without.erase(without.find(str));
    std::string unique;
    for (char c : str) {
      unique += c;
      if (!begins_with(without, unique)) {
        // There is nothing which begins with this, break.
        break;
      }
    }
    map[str] = unique;
  }
  
  return map;  
}
