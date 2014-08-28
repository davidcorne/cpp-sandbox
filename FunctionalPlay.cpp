//=============================================================================
//
// An attempt to try currying and other such things in C++.
//
//

#include "Compiler.h"
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#include <iostream>
#include <string>
#include <functional>

#include "Printer.h"

//=============================================================================
auto if_func = [](bool ok, auto func_a, decltype(func_a) func_b)
{
  return ok ? func_a : func_b;
};

//=============================================================================
auto id = [](auto x)
{
  return [x](){return x;};
};

//=============================================================================
auto subtract = [](auto x, auto y)
{
  return id(x - y);
};

//=============================================================================
auto less = [](auto x, auto y)
{
  return id(x < y);
};
  
//=============================================================================
auto fibonnacci = []() {
  return [](int n) {
    std::function<int(int)> recurse;
    recurse = [&recurse](int i) {
      std::function<int()> one = id(1);
      auto again = [i, &recurse]{
        return recurse(subtract(i, 1)()) + recurse(subtract(i, 2)());
      };
      return if_func(less(i, 3)(), one, again)();
    };
    return recurse(n);
  };
};

//=============================================================================
auto range = [](auto start, auto end, std::function<void(decltype(start))> func) {
  for (auto current = start; current < end; ++current) {
    func(current);
  }
};

//=============================================================================
int main()
{
  range(1, 10, [](int i){print(i, "  ", fibonnacci()(i));});
  range(11, 26, [](int i){print(i, " ", fibonnacci()(i));});
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
