//=============================================================================
//
// An attempt to try currying and other such things in C++.
//
//

#include "Capabilities.h"
#if CAPABILITY_GENERIC_LAMBDAS == 1
#include <iostream>
#include <string>

#include "Functional.h"
#include "Printer.h"

//=============================================================================
auto fibonnacci = [](int n) {
  return [n]() {
    std::function<int(int)> recurse;
    recurse = [&recurse](int i) {
      std::function<int()> one = fnc::unit(1);
      auto again = [i, &recurse]{
        return recurse(fnc::sub(i, 1)()) + recurse(fnc::sub(i, 2)());
      };
      return fnc::if_func(fnc::less(i, 3), one, again)()();
    };
    return recurse(n);
  };
};

//=============================================================================
int main()
{
  fnc::range(1, 10, [](int i){print(i, "  ", fibonnacci(i)());})();
  fnc::range(11, 26, [](int i){print(i, " ", fibonnacci(i)());})();
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_GENERIC_LAMBDAS)
#endif
