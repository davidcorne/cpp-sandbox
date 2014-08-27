//=============================================================================
//
// This defines compiler capabilities.

#include "Compiler.h"
#include "Version.h"

#if COMPILER_TYPE == COMPILER_TYPE_GCC
#if VERSION > 40300
#define VARIADIC_TEMPLATES 1
#endif // VERSION > 40300
#endif

#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#if __has_feature(cxx_variadic_templates)
#define VARIADIC_TEMPLATES 1
#endif // __has_feature(cxx_variadic_templates)
#endif
