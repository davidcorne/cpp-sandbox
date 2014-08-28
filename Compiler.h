//=============================================================================
// Defines for supported compilers.

#ifndef Compiler_H
#define Compiler_H

// Include this for files which won't work under a given compiler.
#include "UnsupportedFeatureMain.h"

#define COMPILER_TYPE_VS 0
#define COMPILER_TYPE_GCC 1
#define COMPILER_TYPE_CLANG 2

#ifdef _MSC_VER
#define COMPILER_TYPE COMPILER_TYPE_VS
#endif // ifdef _MSC_VER

#ifdef __GNUC__
#ifndef __clang__
#define COMPILER_TYPE COMPILER_TYPE_GCC
#else
#define COMPILER_TYPE COMPILER_TYPE_CLANG
#endif // __clang__
#endif // ifdef __GNUC__

#ifndef COMPILER_TYPE
#error "Unknown compiler type."
#endif // COMPILER_TYPE
 
#endif // Compiler_H
