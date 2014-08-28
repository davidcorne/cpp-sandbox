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
auto fibonnacci = [](int n) {
  std::function<int(int)> recurse;
  recurse = [&recurse](int i) {
    int ret_val = 1;
    if (i > 2) {
      ret_val = recurse(i - 1) + recurse(i - 2);
    }
    return ret_val;
  };
  return recurse(n);
};

//=============================================================================
int main()
{
  print(fibonnacci(40));
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
