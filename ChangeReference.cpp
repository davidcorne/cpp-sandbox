//=============================================================================
//
// 

#include <iostream>
#include <string>

#include <UnitCpp/Test.h>

//=============================================================================
class Keeper {
public:

  Keeper(const std::string& name)
    : m_name(name)
    {}

  std::string name() const
    {
      return m_name;
    }

private:
  const std::string& m_name;
};

//=============================================================================
TEST(ChangeReference, change_ref)
{
  std::string name("Fred");
  Keeper keeper(name);
  TEST_EQUAL(keeper.name(), "Fred", "Wrong name");
  name.assign("George");
  TEST_EQUAL(keeper.name(), "George", "Wrong name");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
