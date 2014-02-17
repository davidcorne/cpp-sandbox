//=============================================================================
//
// This is one place to define the compiler guards:
//
// #if GCC_VERSION > XXYYZZ
// ...
// #else
// #include <iostream>
// int main() {
//   std::cout << "C++ 11 not fully supported." << std::endl;
//   return 0;
// }
// #endif
//
#include "gcc_version.h"

#define CPP_ELEVEN_SUPPORTED GCC_VERSION > 40800

#define NOT_SUPPORTED_MAIN \
  int main() {\
  std::cout << "C++ 11 not fully supported." << std::endl;\
   return 0;\
 }\

