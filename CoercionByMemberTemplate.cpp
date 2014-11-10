//=============================================================================
//
// Inspired by:
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Coercion_by_Member_Template

#include "Capabilities.h"
#ifdef VARIADIC_TEMPLATES

#include <assert.h>
#include <iostream>
#include <random>

#include <UnitCpp/Test.h>

//=============================================================================
template <class T>
class Ptr {
public:
  Ptr (T& ptr)
    : m_ptr(&ptr)
    {
      std::cout << m_ptr << std::endl;
      assert(m_ptr);
    }
  
  Ptr (const Ptr& p)
    : m_ptr(p.m_ptr)
    {
    }

  template <class U>
  Ptr (const Ptr<U>& p)
  // Supporting coercion using member template constructor.
  // This is not a copy constructor, but behaves similarly.
    : m_ptr (convert(p)) // Implicit conversion from U to T required
    {
    }
  
  // Copy assignment operator.
  Ptr & operator=(const Ptr& p)
    {
      m_ptr = p.m_ptr;
      return *this;
    }
  
  template <class U>
  Ptr & operator=(const Ptr<U>& p)
  // Supporting coercion using member template assignment operator.
  // This is not the copy assignment operator, but works similarly.
    {
      m_ptr = convert(p); // Implicit conversion from U to T required
      return *this;
    }
  
protected:

  UNITCPP_FRIEND_TEST(CoercionByMemberTemplate, non_null);
  UNITCPP_FRIEND_TEST(CoercionByMemberTemplate, convert);

  template <class U>
  U* convert(const Ptr<U>& p)
    {
      // <nnn> // horrible, needs knowledge that the only member is U*
      // <nnn> Ptr<U>* ptr_u = const_cast<Ptr<U>*>(&p);
      // <nnn> assert(ptr_u);
      // <nnn> U* u = reinterpret_cast<U*>(ptr_u);
      // <nnn> assert(u);
      // <nnn> return u;
      struct Castable {
        U* m_raw_pointer;
      };

      Ptr<U>* non_const_p = const_cast<Ptr<U>*>(&p);
      assert(non_const_p);
      Castable* castable = (Castable*)(non_const_p);
      assert(castable);
      U* u = (U*)(castable);
      return u;
      
    }
  
  T* m_ptr;
};

//=============================================================================
class Base {
};

//=============================================================================
class Derived : public Base {
public:

  Derived()
    : m_rand(0)
    {
      std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution;
      m_rand = distribution(generator);
    }
  
  bool operator==(const Derived& d) {
    return m_rand == d.m_rand;
  }

  int m_rand;
};

//=============================================================================
TEST(CoercionByMemberTemplate, non_null)
{
  Base base;
  Ptr<Base> p_base(base);
  Derived derived;
  Ptr<Derived> p_derived(derived);

  Ptr<Base> new_p_base = p_derived;
  TEST_TRUE(new_p_base.m_ptr, "Non-null pointer.");
}

//=============================================================================
TEST(CoercionByMemberTemplate, convert)
{
  Derived derived;
  Ptr<Derived> p_derived(derived);

  Derived* raw_derived_ptr = p_derived.convert(p_derived);
  TEST_TRUE(raw_derived_ptr, "Null pointer from convert.");

  TEST_EQUAL(raw_derived_ptr->m_rand, derived.m_rand, "Convert failed.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
