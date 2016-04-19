//=============================================================================
//
// 
#include "ObserverPointer.h"

#include <UnitCpp.h>

//=============================================================================
TEST(ObserverPointer, constructors)
{
  ObserverPtr<double> invalid;
  int* i = nullptr;
  ObserverPtr<int> i_observer(i);
  ObserverPtr<double> null = nullptr;
  TEST_FALSE(null);
}

//=============================================================================
TEST(ObserverPointer, operator_bool)
{
  ObserverPtr<std::string> invalid;
  TEST_FALSE(invalid);
  std::unique_ptr<float> f(new float(17.2f));
  ObserverPtr<float> observer(f.get());
  TEST_TRUE(observer);
}

//=============================================================================
TEST(ObserverPointer, equality)
{

}

//=============================================================================
TEST(ObserverPointer, inequality)
{

}

//=============================================================================
TEST(ObserverPointer, copy)
{
  std::unique_ptr<double> p_d(new double(55.5));
  ObserverPtr<double> one(p_d.get());
  ObserverPtr<double> two(one);
  TEST_EQUAL(one, two);
}

//=============================================================================
TEST(ObserverPointer, dereference)
{
  std::unique_ptr<std::string> p_string(new std::string("Hello"));
  ObserverPtr<std::string> string_observer(p_string.get());
  TEST_EQUAL(string_observer.operator->(), p_string.get());

  std::string& dereferenced = *string_observer;
  TEST_EQUAL(dereferenced, *p_string);
}

struct A {
};

struct B : public A {
};

//=============================================================================
TEST(ObserverPointer, conversion)
{
  std::unique_ptr<int> i(new int(5));
  ObserverPtr<int> p_i(i.get());
  ObserverPtr<const int> const_p_i(p_i);
  TEST_EQUAL(p_i.get(), const_p_i.get());

  std::unique_ptr<B> b(new B());
  ObserverPtr<B> observer_b(b.get());
  ObserverPtr<A> observer_a(observer_b);
  TEST_EQUAL(observer_a.get(), observer_b.get());
}

//=============================================================================
TEST(ObserverPointer, const)
{
  // Ensure that a ObserverPtr<const T> will get back a const T*
  int i = 5;
  ObserverPtr<const int> const_observer(&i);
  auto const_ptr = const_observer.get();
  static_assert(
    std::is_const<std::remove_pointer<decltype(const_ptr)>::type>::value,
    "const_ptr should be a const int*"
  );
  ObserverPtr<int> observer(&i);
  auto ptr = observer.get();
  static_assert(
    !std::is_const<std::remove_pointer<decltype(ptr)>::type>::value,
    "ptr should be an int*"
  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
