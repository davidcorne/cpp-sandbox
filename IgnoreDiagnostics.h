//=============================================================================
// This is a compiler independent way of turning off compiler warnings.
// This works by defining the warning you want to turn off, then including this
// file.
//   e.g.
//   #define UNUSED_PRIVATE_FIELD
//   #include "IgnoreDiagnostics.h"
//   #undef UNUSED_PRIVATE_FIELD


#ifndef IgnoreDiagnostics_H
#define IgnoreDiagnostics_H

#include "Compiler.h"

#ifdef UNNEEDED_INTERNAL_DECLARATION
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wunneeded-internal-declaration"
#endif // COMPILER_TYPE
#undef UNNEEDED_INTERNAL_DECLARATION
#endif // UNNEEDED_INTERNAL_DECLARATION

#ifdef UNUSED_PRIVATE_FIELD
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif // COMPILER_TYPE 
#undef UNUSED_PRIVATE_FIELD
#endif // UNUSED_PRIVATE_FIELD

#ifdef UNUSED_VARIABLE
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wunused-variable"
#elif COMPILER_TYPE == COMPILER_TYPE_GCC
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif // COMPILER_TYPE 
#undef UNUSED_VARIABLE
#endif // UNUSED_VARIABLE

#endif
