//=============================================================================
//
// This is an exercise in implementing std::function.

#include "Capabilities.h"
#ifdef CAPABILITY_VARIADIC_TEMPLATES
#include <UnitCpp.h>

#include <memory>

//=============================================================================
template <typename tRETURN, typename... tARGS>
class callable_base {
public:

  virtual tRETURN operator()(tARGS...) = 0;

  virtual std::unique_ptr<callable_base<tRETURN, tARGS...> > clone() const = 0;
  
  virtual ~callable_base() = 0;
  
};

//=============================================================================
template <typename tRETURN, typename... tARGS>
callable_base<tRETURN, tARGS...>::~callable_base()
{
}

//=============================================================================
template <typename tFUNCTION, typename tRETURN, typename... tARGS>
class function_callable : public callable_base<tRETURN, tARGS...> {
public:

  function_callable(tFUNCTION function);

  virtual tRETURN operator()(tARGS... args) override;

  virtual std::unique_ptr<callable_base<tRETURN, tARGS...> > clone() const override;
  
  virtual ~function_callable() {}
  
private:

  tFUNCTION m_function;
};


//=============================================================================
template <typename tFUNCTION, typename tRETURN, typename... tARGS>
function_callable<tFUNCTION, tRETURN, tARGS...>::function_callable(
  tFUNCTION function
)
  : m_function(function)
{
}

//=============================================================================
template <typename tFUNCTION, typename tRETURN, typename... tARGS>
tRETURN function_callable<tFUNCTION, tRETURN, tARGS...>::operator()(
  tARGS... args
)
{
  return m_function(args...);
}

//=============================================================================
template <typename tFUNCTION, typename tRETURN, typename... tARGS>
std::unique_ptr<callable_base<tRETURN, tARGS...> > function_callable<tFUNCTION, tRETURN, tARGS...>::clone() const
{
  return std::unique_ptr<callable_base<tRETURN, tARGS...> >(
    new function_callable<tFUNCTION, tRETURN, tARGS...>(m_function)
  );
}

template <typename>
class function;

//=============================================================================
template <typename tRETURN, typename... tARGS>
class function<tRETURN(tARGS...)> {
public:

  function();

  template <typename tFUNCTION>
  function(tFUNCTION f);

  function(const function<tRETURN(tARGS...)>& other);
  
  function<tRETURN(tARGS...)>& operator=(
    const function<tRETURN(tARGS...)>& other
  );
  
  tRETURN operator()(tARGS...);

  operator bool() const;
  
private:

  std::unique_ptr<callable_base<tRETURN, tARGS...> > m_callable;
  
};

//=============================================================================
template <typename tRETURN, typename... tARGS>
template <typename tFUNCTION>
function<tRETURN(tARGS...)>::function(tFUNCTION func)
  : m_callable(new function_callable<tFUNCTION, tRETURN, tARGS...>(func))
{
}

//=============================================================================
template <typename tRETURN, typename... tARGS>
function<tRETURN(tARGS...)>::function()
  : m_callable(nullptr)
{
}

//=============================================================================
template <typename tRETURN, typename... tARGS>
function<tRETURN(tARGS...)>::function(const function<tRETURN(tARGS...)>& other)
  : m_callable(other.m_callable->clone())
{
}

//=============================================================================
template <typename tRETURN, typename... tARGS>
function<tRETURN(tARGS...)>& function<tRETURN(tARGS...)>::operator=(
  const function<tRETURN(tARGS...)>& other
)
{
  if (this != &other) {
    m_callable = other.m_callable->clone();
  }
  return *this;
}

//=============================================================================
template <typename tRETURN, typename... tARGS>
function<tRETURN(tARGS...)>::operator bool() const
{
  return static_cast<bool>(m_callable);
}

//=============================================================================
void test_callable_function()
{

}

//=============================================================================
TEST(function, ctor)
{
  function<void()> empty_func;
  function<void()> nothing_func([](){});
  function<void()> copy_of_nothing(nothing_func);
  copy_of_nothing = copy_of_nothing;
  function<void()> function_ptr(test_callable_function);
}

//=============================================================================
TEST(function, empty)
{
  function<int()> empty_func;
  bool empty_func_valid = empty_func;
  TEST_FALSE(empty_func_valid);
  function<double()> non_empty_func([](){return 5.3;});
  bool non_empty_func_valid = non_empty_func;
  TEST_TRUE(non_empty_func_valid);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES)
#endif
