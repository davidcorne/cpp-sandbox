//=============================================================================
//
// This defines compiler capabilities.

#include "Compiler.h"
#include "Version.h"
#include "UnsupportedFeatureMain.h"

#if COMPILER_TYPE == COMPILER_TYPE_GCC
#if VERSION > 40300
#define VARIADIC_TEMPLATES 1
#define ATOMICS 1
#define CONSTEXPR 1
#endif // VERSION > 40300

#define DIGRAPHS 1

#endif // COMPILER_TYPE == COMPILER_TYPE_GCC

#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#if __has_feature(cxx_variadic_templates)
#define VARIADIC_TEMPLATES 1
#endif // __has_feature(cxx_variadic_templates)#

#if __has_feature(c_atomic)
#define ATOMICS 1
#endif // __has_feature(c_atomic)

#if __has_feature(cxx_constexpr)
#define CONSTEXPR 1
#endif // __has_feature(cxx_constexpr)

// it appears that __has_feature(cxx_generic_lambdas) is not working in my
// version of clang, just define this if we are in clang.
// <nnn> #if __has_feature(cxx_generic_lambdas)
#define GENERIC_LAMBDAS 1
// <nnn> #endif // __has_feature(cxx_generic_lambdas)

#define DIGRAPHS 1
#endif // COMPILER_TYPE == COMPILER_TYPE_CLANG

#if COMPILER_TYPE == COMPILER_TYPE_VS

// MSVC++ 12.0 VERSION == 1800 (Visual Studio 2013)
// MSVC++ 11.0 VERSION == 1700 (Visual Studio 2012)
// MSVC++ 10.0 VERSION == 1600 (Visual Studio 2010)
// MSVC++ 9.0  VERSION == 1500 (Visual Studio 2008)
// MSVC++ 8.0  VERSION == 1400 (Visual Studio 2005)
// MSVC++ 7.1  VERSION == 1310 (Visual Studio 2003)
// MSVC++ 7.0  VERSION == 1300
// MSVC++ 6.0  VERSION == 1200
// MSVC++ 5.0  VERSION == 1100

#if VERSION >= 1800
#define VARIADIC_TEMPLATES 1
#endif // VERSION >= 1800

#if VERSION >= 1700
#define ATOMICS 1
#endif // VERSION >= 1700

#endif // COMPILER_TYPE == COMPILER_TYPE_VS
