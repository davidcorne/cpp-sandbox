//=============================================================================
// This is a macro which says this code uses a feature which is unsupported by
// the compiler it was compiled in.

#ifndef UnsupportedFeatureMain_H
#define UnsupportedFeatureMain_H

#include <iostream>

#include "Compiler.h"

#define UNSUPPORTED_FEATURE_MAIN(FEATURE)                     \
  int main()                                                  \
  {                                                           \
    std::cout                                                 \
      << "This program uses the compiler feature "            \
      << #FEATURE                                             \
      << " which is not supported by "                        \
      << COMPILER_NAME                                        \
      << " which compiled it."                                \
      << std::endl;                                           \
    return 0;                                                 \
  }                                                           \

#endif
