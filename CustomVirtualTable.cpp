//=============================================================================
//
// This is for when you have to use enums, in preference to a switch statement.

#include <assert.h>
#include <iostream>
#include <functional>
#include <map>
#include <string>

#include <UnitCpp.h>

//=============================================================================
enum SwitchThing {
  One,
  Two,
  Three
};

//=============================================================================
class CustomVirtualTable {
public:
  CustomVirtualTable();

  std::string on(SwitchThing);
  
private:
  std::map<SwitchThing, std::function<std::string()> > m_function_table;

  std::string one() const;
  std::string two() const;
  std::string three() const;
  
};

//=============================================================================
TEST(CustomVirtualTable, switch)
{
  CustomVirtualTable table;
  TEST_EQUAL(table.on(One), "One", "Wrong value from table.");
  TEST_EQUAL(table.on(Two), "Two", "Wrong value from table.");
  TEST_EQUAL(table.on(Three), "Three", "Wrong value from table.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
CustomVirtualTable::CustomVirtualTable()
  : m_function_table()
{
  m_function_table[One] = [this]() -> std::string {return one();};
  m_function_table[Two] = [this]() -> std::string {return two();};
  m_function_table[Three] = [this]() -> std::string {return three();};
}

//=============================================================================
std::string CustomVirtualTable::on(SwitchThing thing)
{
  auto it = m_function_table.find(thing);
  assert(it != m_function_table.end());
  return (it->second)();
}

//=============================================================================
std::string CustomVirtualTable::one() const
{
  return "One";
}

//=============================================================================
std::string CustomVirtualTable::two() const
{
  return "Two";
}

//=============================================================================
std::string CustomVirtualTable::three() const
{
  return "Three";
}

