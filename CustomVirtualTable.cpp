//=============================================================================
//
// This is for when you have to use enums, in preference to a switch statement.

#include "Capabilities.h"
#ifdef VARIADIC_TEMPLATES

#include <iostream>
#include <functional>
#include <map>
#include <string>

#include "UnitTest.h"

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
  
  friend class utest_CustomVirtualTable;
};

//=============================================================================
class utest_CustomVirtualTable : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_switch();
  }

private:

  void test_switch();

};

//=============================================================================
void utest_CustomVirtualTable::test_switch()
{
  print(DGC_CURRENT_FUNCTION);
  CustomVirtualTable table;
  test(table.on(One) == "One", "Wrong value from table.");
  test(table.on(Two) == "Two", "Wrong value from table.");
  test(table.on(Three) == "Three", "Wrong value from table.");
}

//=============================================================================
int main() {
  utest_CustomVirtualTable test;
  test.run_tests();
  return 0;
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

#else
UNSUPPORTED_FEATURE_MAIN
#endif
