//=============================================================================
// In my version of the visual studio compiler, alignof is not supported. But
// you can use __alignof instead. This is a macro to wrap that up.

#ifndef AlignOf_H
#define AlignOf_H

#include "Compiler.h"

#if COMPILER_TYPE == COMPILER_TYPE_VS
#define DGC_ALIGNOF __alignof
#else
#define DGC_ALIGNOF alignof
#endif

#endif
