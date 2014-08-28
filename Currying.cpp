//=============================================================================
//
// An attempt to try currying in C++
//
//

#include "Compiler.h"
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#include <iostream>
#include <string>
#include <functional>


//=============================================================================
auto print = [](std::ostream& os, auto s)
{
  os << s << std::endl;
};

//=============================================================================
int main()
{
  print(std::cout, "hi");
  auto curryed_print = [](auto s){print(std::cout, s);};
  curryed_print("there");
  curryed_print(5);

  auto curry = [](auto binary, auto& x) {
    return [&](auto y) { 
      return binary(x, y);
    };
  };
  curry(print, std::cout)("lastly.");
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
