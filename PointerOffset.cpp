//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"

using namespace std;

const int INT_VALUE = 55;

//=============================================================================
class Dummy {
public:

  Dummy()
    : m_int(INT_VALUE),
      m_double(3.14)
    {}
    
private:
  friend class utest_Dummy;
  
  int m_int;
  double m_double;
};

//=============================================================================
class utest_Dummy : public UnitTest {
public:
  
  void run_tests() {
    print(__FILE__);
    test_standard();
  }
private:
  void test_standard();
  
};

//=============================================================================
void utest_Dummy::test_standard()
{
  print(__func__);
  Dummy d;
  assert(d.m_int == INT_VALUE);
  assert(d.m_double == 3.14);
  Dummy* d_ptr = &d;
  
  int* m_int = reinterpret_cast<int*>(d_ptr);
  test(*m_int == INT_VALUE, "Reinterpret cast failed to get class internals");

  // <nnn> void* offset = reinterpret_cast<char*>(&d);
  // <nnn> offset += sizeof(d);
  // <nnn> cout << sizeof(d.m_int) << " " <<  sizeof(d.m_double) << " " <<  sizeof(d) << " " << offset << endl;
}

//=============================================================================
int main() {
  utest_Dummy test;
  test.run_tests();
  return 0;
}
