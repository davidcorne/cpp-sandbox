//=============================================================================
//
// Not inspired by, but a thought which sprang from
// http://bulldozer00.com/2014/04/17/context-sensitive-keywords/

#include <iostream>

#include <UnitCpp/Test.h>

//=============================================================================
class OverrideBase {
public:

  OverrideBase();
  virtual ~OverrideBase() = 0;

  virtual void do_something() = 0;
  virtual void override() = 0;
  
private:
};

//=============================================================================
class OverrideCls : public OverrideBase {
public:

  OverrideCls();
  virtual ~OverrideCls();

  virtual void do_something() override;

  virtual void override() override;

private:
  friend class utest_OverrideFunction;
};

//=============================================================================
TEST(Overrider, use)
{
  // override is context sensitive, calling a variable this is fine.
  OverrideCls override;
  override.do_something();
  override.override();
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

OverrideBase::OverrideBase(){}
OverrideBase::~OverrideBase(){}

OverrideCls::OverrideCls(){}
OverrideCls::~OverrideCls(){}
void OverrideCls::do_something(){}
void OverrideCls::override(){}
