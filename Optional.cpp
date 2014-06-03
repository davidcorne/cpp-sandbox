//=============================================================================

#include "UnitTest.h"

//=============================================================================
template <typename T>
class Optional {
public:

  Optional();
  // Default constructor

  Optional(const T& t);
  Optional(T&& t);
  // Construct with instances of T
  
  ~Optional();
  // Destructor

  const T& value() const;
  T& value();
  // Get the underlying value
  
  operator bool() const;
  // Is there a value set?

private:

  union {
    T m_value;
  };
  bool m_set;
};


//=============================================================================
class utest_Optional : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_int();
    test_no_default_construction();
    test_no_default_or_copy_construction();
  }

private:

  void test_int();

  void test_no_default_construction();

  void test_no_default_or_copy_construction();


  //===========================================================================
  class NoDefaultConstructor {
  public:
    explicit NoDefaultConstructor(double d)
      : m_d(d)
      {
      }
    double m_d;
  };
    
  //===========================================================================
  class NoDefaultOrCopyConstructor {
  public:
    explicit NoDefaultOrCopyConstructor(double d)
      : m_d(d)
      {
      }
    NoDefaultOrCopyConstructor(NoDefaultOrCopyConstructor&& other)
      : m_d(other.m_d)
      {
      }
      
    NoDefaultOrCopyConstructor& operator=(NoDefaultOrCopyConstructor&& other)
      {
        m_d = other.m_d;
        return *this;
      }
    double m_d;
  private:
    NoDefaultOrCopyConstructor(const NoDefaultOrCopyConstructor&);
    NoDefaultOrCopyConstructor& operator=(const NoDefaultOrCopyConstructor&);
  };
    
};

//=============================================================================
void utest_Optional::test_int()
{
  print(DGC_CURRENT_FUNCTION);
  Optional<int> bad;
  test(!bad, "bad should be bad.");
  Optional<int> good(5);
  test(good, "good should be good.");
  test(good.value() == 5, "value should be 5.");
}

//=============================================================================
void utest_Optional::test_no_default_construction()
{
  print(DGC_CURRENT_FUNCTION);
  Optional<NoDefaultConstructor> bad;
  test(!bad, "bad should be bad.");

  Optional<NoDefaultConstructor> good(NoDefaultConstructor(-2.5));
  test(good, "good should be good.");
}

//=============================================================================
void utest_Optional::test_no_default_or_copy_construction()
{
  print(DGC_CURRENT_FUNCTION);
  Optional<NoDefaultOrCopyConstructor> bad;
  test(!bad, "bad should be bad.");

  NoDefaultOrCopyConstructor instance(-2.5);
  Optional<NoDefaultOrCopyConstructor> good(std::move(instance));
  test(good, "good should be good.");
}

//=============================================================================
int main() {
  utest_Optional test;
  test.run_tests();
  return 0;
}

//=============================================================================
template <typename T>
Optional<T>::Optional()
  : m_set(false)
{
}

//=============================================================================
template <typename T>
Optional<T>::~Optional()
{
  
}

//=============================================================================
template <typename T>
Optional<T>::Optional(const T& t)
  : m_set(true)
{
  m_value = t;
}

//=============================================================================
template <typename T>
Optional<T>::Optional(T&& t)
  : m_set(true)
{
  m_value = std::move(t);
}

//=============================================================================
template <typename T>
Optional<T>::operator bool() const
{
  return m_set;
}

//=============================================================================
template <typename T>
const T& Optional<T>::value() const
{
  assert(m_set);
  return m_value;
}

//=============================================================================
template <typename T>
T& Optional<T>::value()
{
  assert(m_set);
  return m_value;
}


