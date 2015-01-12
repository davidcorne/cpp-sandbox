//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef CAPABILITY_VARIADIC_TEMPLATES
#include <UnitCpp/Test.h>

//=============================================================================
template <typename T>
class ComStyleSmartPointer {
public:

  template <typename... ARGS>
  ComStyleSmartPointer(ARGS... arguments);

  T& get();

  int release();
  int aquire();
  
private:

  ~ComStyleSmartPointer();
  // Can't be made on the stack.
  
  std::unique_ptr<T> m_t;
  int m_count;
};

//=============================================================================
template <typename T>
  template <typename... ARGS>
ComStyleSmartPointer<T>::ComStyleSmartPointer(ARGS... arguments)
  : m_t(nullptr),
    m_count(1)
{
  m_t.reset(new T(arguments...));
}

//=============================================================================
template <typename T>
ComStyleSmartPointer<T>::~ComStyleSmartPointer()
{
  
}

//=============================================================================
template <typename T>
T& ComStyleSmartPointer<T>::get()
{
  return *m_t;
}

//=============================================================================
template <typename T>
int ComStyleSmartPointer<T>::release()
{
  int new_count = --m_count;
  if (m_count <= 0) {
    delete this;
  }
  return new_count;
}

//=============================================================================
template <typename T>
int ComStyleSmartPointer<T>::aquire()
{
  return ++m_count;
}

//=============================================================================
class Uncopyable {
public:

  Uncopyable(int& i, void* p);
  
private:

  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

//=============================================================================
Uncopyable::Uncopyable(int& i, void* p)
{
  // don't bother using these.
  (void)(i);
  (void)(p);
}

//=============================================================================
TEST(ComStyleSmartPointer, int)
{
  ComStyleSmartPointer<int>* i = new ComStyleSmartPointer<int>(5);
  TEST_EQUAL(i->get(), 5);
  int count = i->release();
  TEST_EQUAL(count, 0);
}

//=============================================================================
TEST(ComStyleSmartPointer, uncopyable)
{
  int i = 5;
  auto uncopyable = new ComStyleSmartPointer<Uncopyable>(i, &i);
  int ref_count = uncopyable->aquire();
  ref_count = uncopyable->release();
  TEST_EQUAL(ref_count, 1);
  ref_count = uncopyable->release();
  TEST_EQUAL(ref_count, 0);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES);
#endif
