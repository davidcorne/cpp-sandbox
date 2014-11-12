//=============================================================================
//
// The shortest possible program (won't link in visual studio)

#include "Compiler.h"

#if COMPILER_TYPE != COMPILER_TYPE_VS

int main;

#else
UNSUPPORTED_FEATURE_MAIN(COMPILER_TYPE_VS)
#endif
