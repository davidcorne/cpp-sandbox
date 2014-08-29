//=============================================================================
//
// An attempt to try currying and other such things in C++.
//
//

#include "Capabilities.h"
#ifdef GENERIC_LAMBDAS
#include <iostream>
#include <string>

#include "Functional.h"
#include "Printer.h"

//=============================================================================
auto fibonnacci = [](int n) {
  return [n]() {
    std::function<int(int)> recurse;
    recurse = [&recurse](int i) {
      std::function<int()> one = id(1);
      auto again = [i, &recurse]{
        return recurse(sub(i, 1)()) + recurse(sub(i, 2)());
      };
      return if_func(less(i, 3), one, again)()();
    };
    return recurse(n);
  };
};

//=============================================================================
int main()
{
  range(1, 10, [](int i){print(i, "  ", fibonnacci(i)());})();
  range(11, 26, [](int i){print(i, " ", fibonnacci(i)());})();
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
