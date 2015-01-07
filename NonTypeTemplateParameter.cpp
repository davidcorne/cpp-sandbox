//=============================================================================
//
// This is testing the standard, [temp.param] 14.1.4
// 4 A non-type template-parameter shall have one of the following (optionally
//   cv-qualified) types:
//   (4.1) - integral or enumeration type,
//   (4.2) - pointer to object or pointer to function,
//   (4.3) - lvalue reference to object or lvalue reference to function,
//   (4.4) - pointer to member,
//   (4.5) - std::nullptr_t.
//
// These are examples of all of these uses.

#include <cassert>
#include <cmath>
#include <UnitCpp/Test.h>

//=============================================================================
// (4.1) - integral or enumeration type

//=============================================================================
enum Greeting {
  Hi,
  Hey,
  Hello
};

//=============================================================================
template <int i>
int get_int()
{
  return i;
}

//=============================================================================
template <Greeting type>
std::string greet()
{
  std::string greeting;
  switch (type) {
  case Hi:
    greeting = "Hi";
    break;
  case Hey:
    greeting = "Hey";
    break;
  case Hello:
    greeting = "Hello";
    break;
  default:
    assert(!"Bad enumerator.");
  }
  return greeting;
}

//=============================================================================
TEST(NonTypeTemplateParameter, 4_1)
{
  TEST_EQUAL(get_int<5>(), 5);
  TEST_EQUAL(greet<Hi>(), "Hi");
  TEST_EQUAL(greet<Hey>(), "Hey");
  TEST_EQUAL(greet<Hello>(), "Hello");
}

//=============================================================================
// (4.2) - pointer to object or pointer to function

extern int s_i;
int s_i = 0;

//=============================================================================
template <int* i>
void set_to_1()
{
  *i = 1;
}


//=============================================================================
template<int (*func)()>
int call()
{
  return func();
}

//=============================================================================
int return_5() {
  return 5;
}

//=============================================================================
TEST(NonTypeTemplateParameter, 4_2)
{
  int result = call<&return_5>();
  TEST_EQUAL(result, 5);

  s_i = 0;
  set_to_1<&s_i>();
  TEST_EQUAL(s_i, 1);
}


//=============================================================================
// (4.3) - lvalue reference to object or lvalue reference to function

//=============================================================================
template <int& i>
void set_to_3()
{
  i = 3;
}

//=============================================================================
template <int (&func)()>
int call_ref()
{
  return func();
}

//=============================================================================
TEST(NonTypeTemplateParameter, 4_3)
{
  s_i = 4;
  set_to_3<s_i>();
  TEST_EQUAL(s_i, 3);
  int result = call_ref<return_5>();
  TEST_EQUAL(result, 5);
}

//=============================================================================
// (4.4) - pointer to member.

//=============================================================================
class Point {
public:

  Point(double x, double y)
    : m_x(x),
      m_y(y)
    {}
  
  double x() const {
    return m_x;
  }
  
  double y() const {
    return m_y;
  }

private:
  double m_x;
  double m_y;
};

//=============================================================================
template <double (Point::*p_func)() const>
double get_value(const Point& p)
{
  return (p.*p_func)();
}

//=============================================================================
TEST(NonTypeTemplateParameter, 4_4)
{
  Point p(1, 2);
  double result = get_value<&Point::x>(p);
  TEST_EQUAL(result, 1);
  result = get_value<&Point::y>(p);
  TEST_EQUAL(result, 2);
}

//=============================================================================
// (4.5) - std::nullptr_t.

//=============================================================================
template <std::nullptr_t>
bool ok()
{
  return false;
}

//=============================================================================
TEST(NonTypeTemplateParameter, 4_5)
{
  TEST_FALSE(ok<nullptr>());
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
