//=============================================================================
//
// 

#include <iostream>

#include <UnitCpp.h>

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
class DummyStruct {
public:
  int m_int;
  double m_double;
  int* m_ptr;
};

//=============================================================================
TEST(Dummy, getters)
{
  Dummy d;
  TEST_EQUAL(d.get_int(), 5, "Int getter failed");
  TEST_EQUAL(d.get_double(), 1.2345, "Double getter failed");
  const int* int_ptr = d.get_int_ptr();
  TEST_EQUAL(int_ptr[0], 0, "Int pointer getter failed");
  TEST_EQUAL(int_ptr[1], 2, "Int pointer getter failed");
  TEST_EQUAL(int_ptr[2], 4, "Int pointer getter failed");
  TEST_EQUAL(int_ptr[3], 6, "Int pointer getter failed");
  TEST_EQUAL(int_ptr[4], 8, "Int pointer getter failed");
  
}

//=============================================================================
TEST(DummyStruct, cast)
{
  Dummy d;
  DummyStruct* dummy = reinterpret_cast<DummyStruct*>(&d);
  TEST_TRUE(dummy, "Cast failed");
  TEST_EQUAL(dummy->m_int, d.get_int(), "Cast didn't access private int");
  TEST_EQUAL(dummy->m_double, d.get_double(), "Cast didn't access private double");
  TEST_EQUAL(dummy->m_ptr, d.get_int_ptr(), "Cast didn't access private pointer");
}

//=============================================================================
TEST(DummyStruct, change)
{
  Dummy d;
  DummyStruct* dummy = reinterpret_cast<DummyStruct*>(&d);
  TEST_TRUE(dummy, "Cast failed");
  dummy->m_int = -20;
  TEST_EQUAL(d.get_int(), -20, "Failed to illegally change member data.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
