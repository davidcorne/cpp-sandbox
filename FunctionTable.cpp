//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"

using namespace std;

class V {
public:

  virtual void print() {
    cout << "print" << endl;
  }

};

//=============================================================================
class utest_FunctionTable : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_1();
    test_2();
    // <nnn> unsigned int vtable_address = *reinterpret_cast<unsigned int*>(this);

    // <nnn> typedef void(*function_pointer)(void*);

    // <nnn> function_pointer m_test_1 = (function_pointer)((unsigned int)(vtable_address));

    // <nnn> m_test_1(this);
  }

private:

  virtual void test_1();
  virtual void test_2();
  virtual void test_3();
  virtual void test_4();

};

//=============================================================================
void utest_FunctionTable::test_1()
{
  print(DGC_CURRENT_FUNCTION);
  V v;
  v.print();

}

//=============================================================================
void utest_FunctionTable::test_2()
{
  print(DGC_CURRENT_FUNCTION);
  V v;
  cout << sizeof(v) << endl;
  cout << sizeof(&v) << endl;

}

//=============================================================================
void utest_FunctionTable::test_3()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
void utest_FunctionTable::test_4()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
int main() {
  utest_FunctionTable test;
  test.run_tests();
  return 0;
}
