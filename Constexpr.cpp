//=============================================================================
//
// 
#include "Capabilities.h"
#if CAPABILITY_CONSTEXPR

#include <iostream>

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
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
