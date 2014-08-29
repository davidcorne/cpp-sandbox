//=============================================================================
//
// Some functional support using C++14 lambdas.

#ifndef Functional_H
#define Functional_H

#include "Capabilities.h"

#ifdef GENERIC_LAMBDAS

#include <functional>

//=============================================================================
auto id = [](auto x)
{
  return [x](){return x;};
};

//=============================================================================
auto if_func = [](auto condition, auto func_a, decltype(func_a) func_b)
{
  return id(condition() ? func_a : func_b);
};

//=============================================================================
auto while_func = [](auto condition, auto func)
{
  typedef
    std::function<std::function<void(void)>(decltype(condition), decltype(func))>
    RecursiveFunc;
  RecursiveFunc recurse;
  recurse = [&recurse, condition, func](decltype(condition), decltype(func)) {
    RecursiveFunc again =
      [&recurse, condition, func](decltype(condition), decltype(func)){
        func();
        return recurse(condition, func);
      };
    return if_func(
      condition,
      again,
      [](decltype(condition), decltype(func)){return []{};}
    )()(condition, func);
  };
  return recurse(condition, func);
};

//=============================================================================
auto add = [](auto x, auto y)
{
  return id(x + y);
};
  
//=============================================================================
auto sub = [](auto x, auto y)
{
  return id(x - y);
};

//=============================================================================
auto increment = [](auto x)
{
  return id(++x);
};

//=============================================================================
auto less = [](auto x, auto y)
{
  return id(x < y);
};
  
//=============================================================================
auto range = [](
  auto start,
  auto end,
  std::function<void(decltype(start))> func
) {
  for (auto current = start; less(current, end)(); current = increment(current)()) {
    func(current);
  }
};

#endif // GENERIC_LAMBDAS
#endif
