//=============================================================================
#include <UnitCpp/Test.h>

//=============================================================================
template <typename tFUNCTION>
class RAII {
public:

  ~RAII();
  // Destructor, calls tFUNCTION.

  RAII(RAII&&);
  RAII& operator=(RAII&&);
  // Move constructor/move assignment operator.
  
private:

  RAII(tFUNCTION end_function);
  // Constructor taking a tFUNCTION.
  // Private so this is called only in the factory.
  
  RAII(const RAII&);
  RAII& operator=(const RAII&);
  // Copying is prohibited.

  template <typename T>
  friend RAII<T> make_raii(T end_function);

  tFUNCTION m_end_function;
  bool m_current;
};

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION> make_raii(tFUNCTION end_function);

//=============================================================================
TEST(RAII, make_raii)
{
  auto raii = make_raii([]{});
}

//=============================================================================
TEST(RAII, call)
{
  bool called = false;
  {
    auto raii = make_raii([&called]{called = true;});
    TEST_FALSE(called);
  }
  TEST_TRUE(called);
}

//=============================================================================
TEST(RAII, move)
{
  int times = 0;
  std::function<void()> end_function = [&times](){++times;};
  {
    auto raii_1 = make_raii(end_function);
    TEST_EQUAL(times, 0);
    auto raii_2 = std::move(raii_1);
    TEST_EQUAL(times, 0);
  }
  TEST_EQUAL(times, 1);
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//----- RAII implementation

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION> make_raii(tFUNCTION end_function)
{
  return RAII<tFUNCTION>(end_function);
}

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION>::RAII(tFUNCTION end_function)
  : m_end_function(end_function),
    m_current(true)
{
}

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION>::~RAII()
{
  if (m_current) {
    m_end_function();
  }
}

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION>::RAII(RAII<tFUNCTION>&& raii)
  : m_end_function(raii.m_end_function),
    m_current(raii.m_current)
{
  raii.m_current = false;
}

//=============================================================================
template <typename tFUNCTION>
RAII<tFUNCTION>& RAII<tFUNCTION>::operator=(RAII<tFUNCTION>&& raii)
{
  if (*raii != this) {
    m_end_function = raii.m_end_function;
    m_current = raii.m_current;
    raii.m_current = false;
  }
  return *this;
}

