//=============================================================================
//
// This is for when you have to use enums, in preference to a switch statement.

#include <iostream>
#include <functional>
#include <map>
#include <string>

#include "UnitTest.h"

using namespace std;

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

  string on(SwitchThing);
  
private:
  map<SwitchThing, function<string()> > m_function_table;

  string one() const;
  string two() const;
  string three() const;
  
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
  m_function_table[One] = [this]() -> string {return one();};
  m_function_table[Two] = [this]() -> string {return two();};
  m_function_table[Three] = [this]() -> string {return three();};
}

//=============================================================================
string CustomVirtualTable::on(SwitchThing thing)
{
  auto it = m_function_table.find(thing);
  assert(it != m_function_table.end());
  return (it->second)();
}

//=============================================================================
string CustomVirtualTable::one() const
{
  return "One";
}

//=============================================================================
string CustomVirtualTable::two() const
{
  return "Two";
}

//=============================================================================
string CustomVirtualTable::three() const
{
  return "Three";
}
