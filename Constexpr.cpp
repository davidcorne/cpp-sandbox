//=============================================================================
//
// 

#include "compiler_guards.h"

#include <iostream>

#if CPP_ELEVEN_SUPPORTED
//=============================================================================
constexpr int return_one() {
  return 1;
}

//=============================================================================
int main() {
  std::cout << return_one() << std::endl;
  return 0;
}

#else
NOT_SUPPORTED_MAIN
#endif
