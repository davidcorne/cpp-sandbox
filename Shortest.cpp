//=============================================================================
//
// The shortest possible program (won't link in visual studio)
// Now clang doesn't like main as a global variable.

#include "Compiler.h"

// This is no longer supported in any compiler. (For good reason)
#if 0

int main;

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN(COMPILER_TYPE_VS)
#endif
