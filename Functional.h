//=============================================================================
//
// Some functional support using C++14 lambdas.

#ifndef Functional_H
#define Functional_H

#include "Capabilities.h"

#if CAPABILITY_GENERIC_LAMBDAS

#include <functional>
#include <sstream>

//=============================================================================
namespace fnc {
  
  //===========================================================================
  auto unit = [](auto x)
  {
    return [x](){return x;};
  };
  
  //===========================================================================
  auto null = []()
  {
    return [](){};
  };
    
  //===========================================================================
  auto if_func = [](auto condition, auto func_a, decltype(func_a) func_b)
  {
    return unit(condition() ? func_a : func_b);
  };
  
  //===========================================================================
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
        [](decltype(condition), decltype(func)){return null;}
      )()(condition, func);
    };
    return recurse(condition, func);
  };
 
  //===========================================================================
  auto add = [](auto x, auto y)
  {
    return unit(x + y);
  };
    
  //===========================================================================
  auto sub = [](auto x, auto y)
  {
    return unit(x - y);
  };
  
  //===========================================================================
  auto increment = [](auto x)
  {
    return unit(++x);
  };
  
  //===========================================================================
  auto less = [](auto x, auto y)
  {
    return unit(x < y);
  };

  //===========================================================================
  auto curry = [](auto func, auto... vars)
  {
    return [func, vars...](auto y){return func(vars..., y);};
  };

  //===========================================================================
  auto range = [](auto start, auto end, auto func)
  {
    auto current = start;
    auto condition = [&current, end](){return less(current, end)();};
    auto continue_func = [&current, &func](){
      func(current);
      current = increment(current)();
    };
    return while_func(condition, continue_func);
  };

  //===========================================================================
  auto stringify = [](auto x)
  {    
    std::stringstream ss;
    ss << x;
    return unit(ss.str());
  };

  //===========================================================================
  auto bind = [](auto func)
  {
    return [func](auto callback) {return callback(func());};
  };
  
}
#endif // CAPABILITY_GENERIC_LAMBDAS
#endif
