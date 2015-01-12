//=============================================================================
//
//D

#include "Capabilities.h"
#ifdef CAPABILITY_VARIADIC_TEMPLATES
#include <iostream>

// types: classes, enums, typedefs, namespaces

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
template <typename T, typename... Arguments>
class SingletonManager {
public:

  SingletonManager(Arguments...);

  T& instance();

  ~SingletonManager();

private:

  T m_instance;
};

//=============================================================================
template <typename T, typename... Arguments>
SingletonManager<T, Arguments...>::SingletonManager(Arguments... args)
  : m_instance(args...)
{
  
}

//=============================================================================
template <typename T, typename... Arguments>
T& SingletonManager<T, Arguments...>::instance()
{
  return m_instance;
}

//=============================================================================
template <typename T, typename... Arguments>
SingletonManager<T, Arguments...>::~SingletonManager()
{
  
}

//=============================================================================
class Singleton {
public:

  Singleton(double foo);
  // Constructor.

  void set_foo(double foo);
  double foo() const;
  
  ~Singleton();
  // Destructor.

private:

  double m_foo;
};

// <nnn> would be in source file, so have file scope only, implementation only
static SingletonManager<Singleton, double> s_manager(0);

//=============================================================================
Singleton::Singleton(double foo)
//
//D Default constructor.
//
{
  s_manager.instance().m_foo = foo;
}

//=============================================================================
Singleton::~Singleton()
//
//D Destructor.
//
{
  std::cout << "Deleted" << std::endl;
}

//=============================================================================
void Singleton::set_foo(double foo)
{
  s_manager.instance().m_foo = foo;
}

//=============================================================================
double Singleton::foo() const
{
  return s_manager.instance().m_foo;
}

//=============================================================================
int main()
//
//D The entry point and single function of this program
//
{
  Singleton s(0);
  std::cout << s.foo() << std::endl;
  Singleton b(0);
  b.set_foo(12);
  std::cout << s.foo() << std::endl;
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES)
#endif

