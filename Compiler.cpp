//=============================================================================
// Prints the compiler version.

#include "Compiler.h"
#include <iostream>

//=============================================================================
int main() {
  std::cout
#if COMPILER_TYPE == COMPILER_TYPE_GCC
    << "gcc"
#elif COMPILER_TYPE == COMPILER_TYPE_VS
    << "vs"
#elif COMPILER_TYPE == COMPILER_TYPE_CLANG
    << "clang"
#endif
    << std::endl;
}

