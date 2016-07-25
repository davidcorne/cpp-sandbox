//=============================================================================
//
// This defines compiler capabilities. If there is a feature which a file uses
// in this list it's best to guard it like this:
// #if CAPABILITY_XXX
// ...
// #else
// UNSUPPORTED_FEATURE_MAIN(CAPABILITY_XXX)
// #endif

#include "Compiler.h"
#include "Version.h"
#include "UnsupportedFeatureMain.h"

#ifndef Capabilities_H
#define Capabilities_H

#define CAPABILITY_ATOMICS 1
#define CAPABILITY_CONSTEXPR 1
#define CAPABILITY_DEFAULTED_FUNCTIONS 1
#define CAPABILITY_DEFAULT_FUNCTION_TEMPLATE_ARGS 1
#define CAPABILITY_DELEGATING_CONSTRUCTOR 1
#define CAPABILITY_DIGRAPHS 1
#define CAPABILITY_GENERIC_LAMBDAS 1
#define CAPABILITY_INITIALISER_LISTS 1
#define CAPABILITY_RANGE_BASE_FOR 1
#define CAPABILITY_REGEX 1
#define CAPABILITY_STD_STRING_LITERALS 1
#define CAPABILITY_THREAD 1
#define CAPABILITY_THREAD_LOCAL_VARIABLES 1
#define CAPABILITY_TYPE_TRAITS 1
#define CAPABILITY_USER_DEFINED_LITERALS 1
#define CAPABILITY_VARIADIC_TEMPLATES 1

#if COMPILER_TYPE == COMPILER_TYPE_GCC
#if VERSION < 40900
#undef CAPABILITY_GENERIC_LAMBDAS
#undef CAPABILITY_REGEX
#undef CAPABILITY_STD_STRING_LITERALS
#endif // VERSION > 40900


#endif // COMPILER_TYPE == COMPILER_TYPE_GCC

#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#if !__has_feature(c_atomic)
#undef CAPABILITY_ATOMICS
#endif // __has_feature(c_atomic)

#if !__has_feature(cxx_constexpr)
#undef CAPABILITY_CONSTEXPR
#else
// <nnn> 
#undef CAPABILITY_CONSTEXPR
#endif // __has_feature(cxx_constexpr)

#if !__has_feature(cxx_delegating_constructors)
#undef CAPABILITY_DELEGATING_CONSTRUCTOR
#endif // __has_feature(cxx_delegating_constructors)

#if !__has_feature(cxx_defaulted_functions)
#undef CAPABILITY_DEFAULTED_FUNCTIONS
#endif // __has_feature(cxx_defaulted_functions)

#if !__has_feature(cxx_generalized_initializers)
#undef CAPABILITY_INITIALISER_LISTS
#endif // !__has_feature(cxx_generalized_initializers)

#if !__has_feature(cxx_range_for)
#undef CAPABILITY_RANGE_BASE_FOR
#endif // !__has_feature(cxx_range_for)

#if !__has_feature(cxx_thread_local)
#undef CAPABILITY_THREAD_LOCAL_VARIABLES
#endif // __has_feature(cxx_thread_local)

#if !__has_feature(cxx_user_literals)
#undef CAPABILITY_USER_DEFINED_LITERALS
#endif //!__has_feature(cxx_user_literals)

#if !__has_feature(cxx_variadic_templates)
#undef CAPABILITY_VARIADIC_TEMPLATES
#endif // __has_feature(cxx_variadic_templates)

#if !__has_feature(cxx_default_function_template_args)
#undef CAPABILITY_DEFAULT_FUNCTION_TEMPLATE_ARGS
#endif // __has_feature(cxx_variadic_templates)

// it appears that __has_feature(cxx_generic_lambdas) is not working in my
// version of clang.
// <nnn> #if ! __has_feature(cxx_generic_lambdas)
#undef CAPABILITY_GENERIC_LAMBDAS
// <nnn> #endif // __has_feature(cxx_generic_lambdas)

// There doesn't appear to be a __has_feature for std::string literals :(
#undef CAPABILITY_STD_STRING_LITERALS

#endif // COMPILER_TYPE == COMPILER_TYPE_CLANG

#if COMPILER_TYPE == COMPILER_TYPE_VS
// MSVC++ 14.0 VERSION == 1900 (Visual Studio 2015)
// MSVC++ 12.0 VERSION == 1800 (Visual Studio 2013)
// MSVC++ 11.0 VERSION == 1700 (Visual Studio 2012)
// MSVC++ 10.0 VERSION == 1600 (Visual Studio 2010)
// MSVC++ 9.0  VERSION == 1500 (Visual Studio 2008)
// MSVC++ 8.0  VERSION == 1400 (Visual Studio 2005)
// MSVC++ 7.1  VERSION == 1310 (Visual Studio 2003)
// MSVC++ 7.0  VERSION == 1300
// MSVC++ 6.0  VERSION == 1200
// MSVC++ 5.0  VERSION == 1100

#undef CAPABILITY_DIGRAPHS
#undef CAPABILITY_CONSTEXPR
#undef CAPABILITY_DEFAULT_FUNCTION_TEMPLATE_ARGS

// VS14 CTP1
#if VERSION < 1900
#undef CAPABILITY_USER_DEFINED_LITERALS
#undef CAPABILITY_DEFAULTED_FUNCTIONS
#undef CAPABILITY_GENERIC_LAMBDAS
#endif // VERSION < 1900

#if VERSION < 1800
#undef CAPABILITY_DELEGATING_CONSTRUCTOR
#undef CAPABILITY_INITIALISER_LISTS
#undef CAPABILITY_VARIADIC_TEMPLATES
#endif // VERSION < 1800

#if VERSION < 1700
#undef CAPABILITY_ATOMICS
#undef CAPABILITY_RANGE_BASE_FOR
#undef CAPABILITY_THREAD
#undef CAPABILITY_TYPE_TRAITS
#endif // VERSION < 1700

#if VERSION < 1700
#undef CAPABILITY_ATOMICS
#undef CAPABILITY_RANGE_BASE_FOR
#undef CAPABILITY_THREAD
#undef CAPABILITY_TYPE_TRAITS
#endif // VERSION < 1700

#if VERSION < 1900
#undef CAPABILITY_STD_STRING_LITERALS
#endif

#endif // COMPILER_TYPE == COMPILER_TYPE_VS
#endif
