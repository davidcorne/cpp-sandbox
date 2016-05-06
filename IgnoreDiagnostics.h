//=============================================================================
// This is a compiler independent way of turning off compiler warnings.
// This works by defining the warning you want to turn off, then including this
// file.
//   e.g.
//   #define UNUSED_PRIVATE_FIELD
//   #include "IgnoreDiagnostics.h"
//   #undef UNUSED_PRIVATE_FIELD

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
#elif COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4101 4189)
#endif // COMPILER_TYPE 
#undef UNUSED_VARIABLE
#endif // UNUSED_VARIABLE

#ifdef RECURSIVE_ON_ALL_PATHS
#if COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4717)
#endif // COMPILER_TYPE 
#undef RECURSIVE_ON_ALL_PATHS
#endif // UNUSED_VARIABLE

#ifdef CONSTANT_CONDITIONAL
#if COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4127)
#endif // COMPILER_TYPE 
#undef RECURSIVE_ON_ALL_PATHS
#endif // UNUSED_VARIABLE

#ifdef IMPLICIT_EXCEPTION_SPEC_MISMATCH
#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#pragma clang diagnostic ignored "-Wimplicit-exception-spec-mismatch"
#endif // COMPILER_TYPE == COMPILER_TYPE_CLANG
#undef IMPLICIT_EXCEPTION_SPEC_MISMATCH
#endif // IMPLICIT_EXCEPTION_SPEC_MISMATCH

#ifdef LOSS_OF_DATA_CONVERSION
#if COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4244 4267)
#endif // COMPILER_TYPE 
#undef LOSS_OF_DATA_CONVERSION
#endif // LOSS_OF_DATA_CONVERSION

#ifdef UNUSED_PARAMETER
#if COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4100)
#endif // COMPILER_TYPE 
#undef UNUSED_PARAMETER
#endif // UNUSED_PARAMETER

#ifdef UNUSED_TYPEDEF
#if COMPILER_TYPE == COMPILER_TYPE_GCC
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif // COMPILER_TYPE 
#undef UNUSED_TYPEDEF
#endif // UNUSED_TYPEDEF

#ifdef UNREACHABLE_CODE
#if COMPILER_TYPE == COMPILER_TYPE_VS
#pragma warning(disable : 4702)
#endif // COMPILER_TYPE 
#undef UNREACHABLE_CODE
#endif // UNREACHABLE_CODE

