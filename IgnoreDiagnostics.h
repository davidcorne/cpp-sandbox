//=============================================================================
// This is a compiler independent way of turning off compiler warnings.
// This works by defining the warning you want to turn off, then including this
// file.

#ifndef IgnoreDiagnostics_H
#define IgnoreDiagnostics_H

#include "Compiler.h"

#ifdef UNNEEDED_INTERNAL_DECLARATION
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wunneeded-internal-declaration"
#endif // COMPILER_TYPE 
#endif // UNNEEDED_INTERNAL_DECLARATION

#ifdef UNUSED_PRIVATE_FIELD
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif // COMPILER_TYPE 
#endif // UNUSED_PRIVATE_FIELD

#endif
