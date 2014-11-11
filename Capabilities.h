//=============================================================================
//
// This defines compiler capabilities.

#include "Compiler.h"
#include "Version.h"
#include "UnsupportedFeatureMain.h"

#ifndef Capabilities_H
#define Capabilities_H

#define CAPABILITY_ATOMICS 1
#define CAPABILITY_CONSTEXPR 1
#define CAPABILITY_DIGRAPHS 1
#define CAPABILITY_GENERIC_LAMBDAS 1
#define CAPABILITY_THREAD_LOCAL_VARIABLES 1
#define CAPABILITY_VARIADIC_TEMPLATES 1

#if COMPILER_TYPE == COMPILER_TYPE_GCC
#if VERSION < 40900
#undef CAPABILITY_GENERIC_LAMBDAS
#define CAPABILITY_GENERIC_LAMBDAS 0
#endif // VERSION > 40900


#endif // COMPILER_TYPE == COMPILER_TYPE_GCC

#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#if !__has_feature(c_atomic)
#undef CAPABILITY_ATOMICS
#define CAPABILITY_ATOMICS 0
#endif // __has_feature(c_atomic)

#if !__has_feature(cxx_constexpr)
#undef CAPABILITY_CONSTEXPR
#define CAPABILITY_CONSTEXPR 0
#endif // __has_feature(cxx_constexpr)

#if !__has_feature(cxx_thread_local)
#undef CAPABILITY_THREAD_LOCAL_VARIABLES
#define CAPABILITY_THREAD_LOCAL_VARIABLES 0
#endif // __has_feature(cxx_thread_local)

#if !__has_feature(cxx_variadic_templates)
#undef CAPABILITY_VARIADIC_TEMPLATES
#define CAPABILITY_VARIADIC_TEMPLATES 0
#endif // __has_feature(cxx_variadic_templates)

// it appears that __has_feature(cxx_generic_lambdas) is not working in my
// version of clang.
// <nnn> #if ! __has_feature(cxx_generic_lambdas)
// <nnn> #undef CAPABILITY_GENERIC_LAMBDAS
// <nnn> #define CAPABILITY_GENERIC_LAMBDAS 0
// <nnn> #endif // __has_feature(cxx_generic_lambdas)

#endif // COMPILER_TYPE == COMPILER_TYPE_CLANG

#if COMPILER_TYPE == COMPILER_TYPE_VS
#undef CAPABILITY_DIGRAPHS
#define CAPABILITY_DIGRAPHS 0
// MSVC++ 12.0 VERSION == 1800 (Visual Studio 2013)
// MSVC++ 11.0 VERSION == 1700 (Visual Studio 2012)
// MSVC++ 10.0 VERSION == 1600 (Visual Studio 2010)
// MSVC++ 9.0  VERSION == 1500 (Visual Studio 2008)
// MSVC++ 8.0  VERSION == 1400 (Visual Studio 2005)
// MSVC++ 7.1  VERSION == 1310 (Visual Studio 2003)
// MSVC++ 7.0  VERSION == 1300
// MSVC++ 6.0  VERSION == 1200
// MSVC++ 5.0  VERSION == 1100

#if VERSION < 1800
#undef CAPABILITY_VARIADIC_TEMPLATES
#define CAPABILITY_VARIADIC_TEMPLATES 0
#endif // VERSION >= 1800

#if VERSION < 1700
#undef CAPABILITY_ATOMICS
#define CAPABILITY_ATOMICS 0
#endif // VERSION >= 1700

#endif // COMPILER_TYPE == COMPILER_TYPE_VS
#endif
