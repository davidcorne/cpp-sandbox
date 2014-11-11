//=============================================================================
#include "Compiler.h"

#if COMPILER_TYPE != COMPILER_TYPE_VS

#include <iostream>


#define UNUSED_VARIABLE 1
#include "IgnoreDiagnostics.h"

#define UT_JOIN(a, args...) a ## args

//=============================================================================
int main() {
  int ab = 2;
  int abc = 53;
  int cd = UT_JOIN(a, b, c);
  std::cout << cd << std::endl;
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif
