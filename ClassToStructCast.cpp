//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef VARIADIC_TEMPLATES

#include <iostream>

#include "UnitTest.h"

//=============================================================================
class Dummy {
public:
  Dummy()
    : m_int(5),
      m_double(1.2345),
      m_ptr(0)
    {
      int size = 5;
      m_ptr = new int[size];
      for (int i = 0; i < size; ++i) {
        m_ptr[i] = 2 * i;
      }
    }

  int get_int() const {
    return m_int;
  }
  
  double get_double() const {
    return m_double;
  }
  
  const int* get_int_ptr() const {
    return m_ptr;
  }
  
  ~Dummy() {
    delete[] m_ptr;
  }
  
private:
  int m_int;
  double m_double;
  int* m_ptr;
};

//=============================================================================
class utest_Dummy : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_getters();
  }

private:

  void test_getters();

};

//=============================================================================
void utest_Dummy::test_getters()
{
  print(DGC_CURRENT_FUNCTION);
  Dummy d;
  test(d.get_int() == 5, "Int getter failed");
  test(d.get_double() == 1.2345, "Double getter failed");
  const int* int_ptr = d.get_int_ptr();
  test(int_ptr[0] == 0, "Int pointer getter failed");
  test(int_ptr[1] == 2, "Int pointer getter failed");
  test(int_ptr[2] == 4, "Int pointer getter failed");
  test(int_ptr[3] == 6, "Int pointer getter failed");
  test(int_ptr[4] == 8, "Int pointer getter failed");
  
}

//=============================================================================
class DummyStruct {
public:
  int m_int;
  double m_double;
  int* m_ptr;
};


  
//=============================================================================
class utest_DummyStruct : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_cast();
    test_change();
  }

private:

  void test_cast();
  void test_change();

};

//=============================================================================
void utest_DummyStruct::test_cast()
{
  print(DGC_CURRENT_FUNCTION);
  Dummy d;
  DummyStruct* dummy = reinterpret_cast<DummyStruct*>(&d);
  test(dummy, "Cast failed");
  test(dummy->m_int == d.get_int(), "Cast didn't access private int");
  test(dummy->m_double == d.get_double(), "Cast didn't access private double");
  test(dummy->m_ptr == d.get_int_ptr(), "Cast didn't access private pointer");
}

//=============================================================================
void utest_DummyStruct::test_change()
{
  print(DGC_CURRENT_FUNCTION);
  Dummy d;
  DummyStruct* dummy = reinterpret_cast<DummyStruct*>(&d);
  test(dummy, "Cast failed");
  dummy->m_int = -20;
  test(d.get_int() == -20, "Failed to illegally change member data.");
}

//=============================================================================
int main() {
  utest_Dummy dummy_test;
  dummy_test.run_tests();
  utest_DummyStruct dummy_struct_test;
  dummy_struct_test.run_tests();
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
