//=============================================================================
//
// 

#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class Keeper {
public:

  Keeper(const string& name)
    : m_name(name)
    {}

  string name() const
    {
      return m_name;
    }

private:
  friend class utest_ChangeReference;
  const string& m_name;
};

//=============================================================================
class utest_ChangeReference : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_change_ref();
  }

private:

  void test_change_ref();

};

//=============================================================================
void utest_ChangeReference::test_change_ref()
{
  print(DGC_CURRENT_FUNCTION);
  string name("Fred");
  Keeper keeper(name);
  test(keeper.name() == "Fred", "Wrong name");
  name.assign("George");
  test(keeper.name() == "George", "Wrong name");
}

//=============================================================================
int main() {
  utest_ChangeReference test;
  test.run_tests();
  return 0;
}