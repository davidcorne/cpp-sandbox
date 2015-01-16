//=============================================================================
#include <functional>

#include <UnitCpp.h>

//=============================================================================
class RAII {
public:

  ~RAII();
  // Destructor, calls tFUNCTION.

  RAII(RAII&&);
  RAII& operator=(RAII&&);
  // Move constructor/move assignment operator.

private:

  RAII(std::function<void()> end_function);
  // Constructor taking a tFUNCTION.
  // Private so this is called only in the factory.
  
  RAII(const RAII&);
  RAII& operator=(const RAII&);
  // Copying is prohibited.

  template <typename T>
  friend RAII make_raii(T end_function);

  std::function<void()> m_end_function;
  bool m_current;
};

//=============================================================================
template <typename tFUNCTION>
RAII make_raii(tFUNCTION end_function);

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
TEST(RAII, move2)
{
  int times = 0;
  std::function<void()> end_function = [&times](){++times;};
  {
    auto raii_1 = make_raii(end_function);
    {
      auto raii_2 = make_raii(end_function);
      TEST_EQUAL(times, 0);
      {
        auto raii_3 = std::move(raii_1);
        TEST_EQUAL(times, 0);
        // here raii_3 will have destructed the ownership of raii_1
      }
      TEST_EQUAL(times, 1);
    }
    // here raii_2 will have destructed.
  }
  TEST_EQUAL(times, 2);
}

//=============================================================================
// This stubs a class which aquires a resource and manages access to it, so it
// keeps an RAII as a member.
class TestResourceWrapper {
public:

  TestResourceWrapper();

private:

  void free_resource(int& resource) const {
    resource = -1;
  }
  void aquire_resource(int& resource) const {
    resource = 5;
  }

  RAII m_raii;
};

static int RESOURCE = -1;

//=============================================================================
TestResourceWrapper::TestResourceWrapper()
  : m_raii(make_raii([](){}))
{
  aquire_resource(RESOURCE);
  m_raii = make_raii([this](){free_resource(RESOURCE);});
}

//=============================================================================
TEST(RAII, ClassManager)
{
  TEST_EQUAL(RESOURCE, -1);
  {
    TestResourceWrapper wrapper;
    TEST_EQUAL(RESOURCE, 5);
  }
  TEST_EQUAL(RESOURCE, -1);
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//----- RAII implementation

//=============================================================================
template <typename tFUNCTION>
RAII make_raii(tFUNCTION end_function)
{
  return RAII(end_function);
}

//=============================================================================
RAII::RAII(std::function<void()> end_function)
  : m_end_function(end_function),
    m_current(true)
{
}

//=============================================================================
RAII::~RAII()
{
  if (m_current) {
    m_end_function();
  }
}

//=============================================================================
RAII::RAII(RAII&& raii)
  : m_end_function(raii.m_end_function),
    m_current(raii.m_current)
{
  raii.m_current = false;
}

//=============================================================================
RAII& RAII::operator=(RAII&& raii)
{
  if (&raii != this) {
    m_end_function = raii.m_end_function;
    m_current = raii.m_current;
    raii.m_current = false;
  }
  return *this;
}

