//=============================================================================
//
// The shortest possible program (won't link in visual studio)
// Now clang doesn't like main as a global variable.

#include "Compiler.h"

#if COMPILER_TYPE == COMPILER_TYPE_GCC

int main;

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN(COMPILER_TYPE_VS)
#endif
