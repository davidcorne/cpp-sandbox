//=============================================================================
//
// This shows how the closure problem from python/dynamic languages works in
// C++.

#include "Capabilities.h"
#if CAPABILITY_RANGE_BASE_FOR
#include <functional>
#include <iostream>
#include <vector>

#include <UnitCpp/Test.h>

//=============================================================================
void out_closure(std::ostream& os)
{
  std::vector<std::function<int()>> functions;
  for (int i = 0; i < 10; ++i) {
    functions.push_back([i](){return i*i;});
  }
  for (auto func: functions) {
    os << func() << std::endl;
  }
}

//=============================================================================
void out_closure2(std::ostream& os)
{
  int current = -1;
  auto func = [&current](){++current; return current * current;};
  for (int i = 0; i < 10; ++i) {
    os << func() << std::endl;
  }
}

//=============================================================================
void out_closure3(std::ostream& os)
{
  int call_number = -1;
  auto func = [&call_number]() -> std::function<int()> {
    ++call_number;
    return call_number < 10 ?
           [call_number](){return call_number * call_number;} :
           std::function<int()>(0);
  };
  auto out = func();
  while (out) {
    os << out() << std::endl;
    out = func();
  }
}

//=============================================================================
TEST(ClosureList, out_closure)
{
  std::stringstream ss;
  out_closure(ss);
  TEST_EQUAL(
    ss.str(),
    "0\n1\n4\n9\n16\n25\n36\n49\n64\n81\n"
  );
  ss.str("");
  out_closure2(ss);
  TEST_EQUAL(
    ss.str(),
    "0\n1\n4\n9\n16\n25\n36\n49\n64\n81\n"
  );
  ss.str("");
  out_closure3(ss);
  std::cout << ss.str() << std::endl;
  TEST_EQUAL(
    ss.str(),
    "0\n1\n4\n9\n16\n25\n36\n49\n64\n81\n"
  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_RANGE_BASE_FOR)
#endif
