//=============================================================================
// Defines for supported compilers.

#ifndef Compiler_H
#define Compiler_H

#define COMPILER_TYPE_VS 0
#define COMPILER_TYPE_GCC 1
#define COMPILER_TYPE_CLANG 2

#ifdef __GNUC__
#ifndef __clang__
#define COMPILER_TYPE COMPILER_TYPE_GCC
#define COMPILER_NAME "gcc"
#else
#define COMPILER_TYPE COMPILER_TYPE_CLANG
#define COMPILER_NAME "clang"
#endif // __clang__
#else
#ifdef _MSC_VER
#define COMPILER_TYPE COMPILER_TYPE_VS
#define COMPILER_NAME "vs"
#endif // ifdef _MSC_VER
#endif // ifdef __GNUC__

#ifndef COMPILER_TYPE
#error "Unknown compiler type."
#endif // COMPILER_TYPE

#ifndef COMPILER_NAME
#error "Unknown compiler name."
#endif // COMPILER_NAME

#endif // Compiler_H
