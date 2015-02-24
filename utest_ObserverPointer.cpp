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
}

//=============================================================================
TEST(ObserverPointer, operator_bool)
{
  ObserverPtr<std::string> invalid;
  TEST_FALSE(invalid);
  std::unique_ptr<float> f(new float(17.2));
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
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
