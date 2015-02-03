//=============================================================================
//
// 

#include <algorithm>
#include <functional>

#include <UnitCpp.h>

//=============================================================================
template <typename tTYPE_A, typename tTYPE_B, typename tRETURN_TYPE>
class BoundNamedOperator {
public:

  template <typename tFUNCTION>
  BoundNamedOperator(tFUNCTION function, tTYPE_A bound_value)
    : m_function(function),
      m_bound_value(bound_value)
    {}

  tRETURN_TYPE result(tTYPE_B b) {
    return m_function(m_bound_value, b);
  }
  
private:
  std::function<tRETURN_TYPE(tTYPE_A, tTYPE_B)> m_function;
  tTYPE_A m_bound_value;
};

//=============================================================================
template <typename tTYPE_A, typename tTYPE_B, typename tRETURN_TYPE>
class NamedOperator {
public:

  template <typename tFUNCTION>
  NamedOperator(tFUNCTION function)
    : m_function(function)
    {}

  BoundNamedOperator<tTYPE_A, tTYPE_B, tRETURN_TYPE> bound(tTYPE_A a) {
    return BoundNamedOperator<tTYPE_A, tTYPE_B, tRETURN_TYPE>(m_function, a);
  }
  
private:
  std::function<tRETURN_TYPE(tTYPE_A, tTYPE_B)> m_function;
};

//=============================================================================
template <typename tTYPE_A, typename tTYPE_B, typename tRETURN_TYPE>
BoundNamedOperator<tTYPE_A, tTYPE_B, tRETURN_TYPE> operator<(
  tTYPE_A a,
  NamedOperator<tTYPE_A, tTYPE_B, tRETURN_TYPE> op
)
{
  return op.bound(a);
}

//=============================================================================
template <typename tTYPE_A, typename tTYPE_B, typename tRETURN_TYPE>
tRETURN_TYPE operator>(
  BoundNamedOperator<tTYPE_A, tTYPE_B, tRETURN_TYPE> bound_operator,
  tTYPE_B b
)
{
  return bound_operator.result(b);
}


auto add = NamedOperator<int, int, int>([](int a, int b)->int{return a + b;});

auto in = NamedOperator<double, std::vector<double>, bool>(
  [](double a, std::vector<double> v)->bool{return std::find(begin(v), end(v), a) != end(v);}
);

//=============================================================================
TEST(NamedOperators, add)
{
  int a = 1;
  int b = 5;
  int result = a <add> b;
  TEST_EQUAL(result, 6);
}

//=============================================================================
TEST(NamedOperators, in)
{
  std::vector<double> vector;
  vector.push_back(55.3);
  vector.push_back(10);

  TEST_TRUE(10.0 <in> vector);
  TEST_TRUE(55.3 <in> vector);
  TEST_FALSE(-7.5 <in> vector);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
