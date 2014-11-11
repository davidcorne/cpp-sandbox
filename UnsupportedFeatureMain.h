//=============================================================================
// This is a macro which says this code uses a feature which is unsupported by
// the compiler it was compiled in.

#ifndef UnsupportedFeatureMain_H
#define UnsupportedFeatureMain_H

#include <iostream>

#define UNSUPPORTED_FEATURE_MAIN                              \
  int main()                                                  \
  {                                                           \
    std::cout                                                 \
      << "This program uses a compiler feature which is not " \
      << "supported by the compiler used in it's creation."   \
      << std::endl;                                           \
    return 0;                                                 \
  }                                                           \

#endif
