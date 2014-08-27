//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef VARIADIC_TEMPLATES

#include <iostream>
#include <functional>

#include "UnitTest.h"

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
class utest_Closure : public UnitTest {
public:

  void run_tests() {
    test_counter();
    test_class_counter();
    test_class_in_counter();
  }

private:

  void test_counter();
  void test_class_counter();
  void test_class_in_counter();

};

//=============================================================================
void utest_Closure::test_counter()
{
  print(DGC_CURRENT_FUNCTION);
  std::function<int(void)> func = counter();
  test(func() == 1, "First call should be 1");
  test(func() == 2, "Second call should be 2");
  test(func() == 3, "Third call should be 3");
  test(func() == 4, "Fourth call should be 4");
}

//=============================================================================
void utest_Closure::test_class_counter()
{
  print(DGC_CURRENT_FUNCTION);
  ClassCounter<int> counter(0);
  std::function<int(void)> func = counter;
  test(func() == 1, "First call should be 1");
  test(func() == 2, "Second call should be 2");
  test(func() == 3, "Third call should be 3");
  test(func() == 4, "Fourth call should be 4");
}

//=============================================================================
void utest_Closure::test_class_in_counter()
{
  print(DGC_CURRENT_FUNCTION);
  std::function<int(void)> func = class_in_counter();
  test(func() == 1, "First call should be 1");
  test(func() == 2, "Second call should be 2");
  test(func() == 3, "Third call should be 3");
  test(func() == 4, "Fourth call should be 4");
}

//=============================================================================
int main() {
  utest_Closure test;
  test.run_tests();
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
