//=============================================================================
//
// 

#include <iostream>
#include <functional>

#include <UnitCpp.h>

//=============================================================================
template <class T>
class ClassCounter : std::unary_function<void, T> {
public:
  ClassCounter(T start)
    : m_count(start) {}
  
  T operator()()
    {
      ++m_count;
      return m_count;
    }
  
private:
  T m_count;
};

//=============================================================================
std::function<int(void)> counter()
{
  static int count = 0;
  std::function<int(void)> increment = [&]() -> int {
    ++count;
    return count;
  };
  return increment;
}

//=============================================================================
std::function<int(void)> class_in_counter()
{
  ClassCounter<int> counter(0);
  return counter;
}

//=============================================================================
TEST(Closure, counter)
{
  std::function<int(void)> func = counter();
  TEST_EQUAL(func(), 1, "First call should be 1");
  TEST_EQUAL(func(), 2, "Second call should be 2");
  TEST_EQUAL(func(), 3, "Third call should be 3");
  TEST_EQUAL(func(), 4, "Fourth call should be 4");
}

//=============================================================================
TEST(Closure, class_counter)
{
  ClassCounter<int> counter(0);
  std::function<int(void)> func = counter;
  TEST_EQUAL(func(), 1, "First call should be 1");
  TEST_EQUAL(func(), 2, "Second call should be 2");
  TEST_EQUAL(func(), 3, "Third call should be 3");
  TEST_EQUAL(func(), 4, "Fourth call should be 4");
}

//=============================================================================
TEST(Closure, class_in_counter)
{
  std::function<int(void)> func = class_in_counter();
  TEST_EQUAL(func(), 1, "First call should be 1");
  TEST_EQUAL(func(), 2, "Second call should be 2");
  TEST_EQUAL(func(), 3, "Third call should be 3");
  TEST_EQUAL(func(), 4, "Fourth call should be 4");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

