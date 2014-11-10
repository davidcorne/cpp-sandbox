//=============================================================================

#include <assert.h>

#include <UnitCpp/Test.h>

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
class NoDefaultConstructor {
public:
  explicit NoDefaultConstructor(double d)
    : m_d(d)
    {
    }
  double m_d;
};
    
//=============================================================================
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

//=============================================================================
TEST(Optional, int)
{
  Optional<int> bad;
  TEST_FALSE(bad, "bad should be bad.");
  Optional<int> good(5);
  TEST_TRUE(good, "good should be good.");
  TEST_EQUAL(good.value(), 5, "value should be 5.");
}

//=============================================================================
TEST(Optional, no_default_construction)
{
  Optional<NoDefaultConstructor> bad;
  TEST_FALSE(bad, "bad should be bad.");

  Optional<NoDefaultConstructor> good(NoDefaultConstructor(-2.5));
  TEST_TRUE(good, "good should be good.");
}

//=============================================================================
TEST(Optional, no_default_or_copy_construction)
{
  Optional<NoDefaultOrCopyConstructor> bad;
  TEST_FALSE(bad, "bad should be bad.");

  NoDefaultOrCopyConstructor instance(-2.5);
  Optional<NoDefaultOrCopyConstructor> good(std::move(instance));
  TEST_TRUE(good, "good should be good.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
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


