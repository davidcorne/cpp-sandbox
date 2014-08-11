//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"

//=============================================================================
class UndefinedClass;

//=============================================================================
class utest_UndefinedClass : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_pointer();
    test_reference();
  }

private:

  void test_pointer();
  void test_reference();

};

//=============================================================================
void utest_UndefinedClass::test_pointer()
{
  print(DGC_CURRENT_FUNCTION);
  UndefinedClass* undef = 0;
  test(!undef, "undef should be null");
  undef = reinterpret_cast<UndefinedClass*>(new int);
  test(undef, "undef shoulf not be null.");
}

//=============================================================================
void utest_UndefinedClass::test_reference()
{
  print(DGC_CURRENT_FUNCTION);
  UndefinedClass& undef = *reinterpret_cast<UndefinedClass*>(new int);
  test(&undef, "undef is not null.");
}

//=============================================================================
int main() {
  utest_UndefinedClass test;
  test.run_tests();
  return 0;
}
