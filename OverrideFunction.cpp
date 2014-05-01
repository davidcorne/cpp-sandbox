//=============================================================================
//
// Not inspired by, but a thought which sprang from
// http://bulldozer00.com/2014/04/17/context-sensitive-keywords/

#include <iostream>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class OverrideBase {
public:

  OverrideBase();
  virtual ~OverrideBase() = 0;

  virtual void do_something() = 0;
  virtual void override() = 0;
  
private:
  friend class utest_OverrideFunction;
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
class utest_OverrideFunction : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_use_override();
  }

private:

  void test_use_override();

};

//=============================================================================
void utest_OverrideFunction::test_use_override()
{
  print(DGC_CURRENT_FUNCTION);
  // override is context sensitive, calling a variable this is fine.
  OverrideCls override;
  override.do_something();
  override.override();
}

//=============================================================================
int main() {
  utest_OverrideFunction test;
  test.run_tests();
  return 0;
}

OverrideBase::OverrideBase(){}
OverrideBase::~OverrideBase(){}

OverrideCls::OverrideCls(){}
OverrideCls::~OverrideCls(){}
void OverrideCls::do_something(){}
void OverrideCls::override(){}
