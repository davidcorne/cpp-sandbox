//=============================================================================
//
// Prints out the capabilities of the current compiler.

#include <iostream>
#include <iomanip>
#include "Capabilities.h"

#define DISPLAY_SUPPORTED(name)\
  std::cout << "Feature: " << std::left << std::setw(35) << #name << " enabled" << std::endl

#define DISPLAY_UNSUPPORTED(name)\
  std::cout << "Feature: " << std::left << std::setw(35) << #name << " disabled" << std::endl

//=============================================================================
int main() {
#ifdef CAPABILITY_ATOMICS
  DISPLAY_SUPPORTED(CAPABILITY_ATOMICS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_ATOMICS);
#endif

#ifdef CAPABILITY_CONSTEXPR
  DISPLAY_SUPPORTED(CAPABILITY_CONSTEXPR);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_CONSTEXPR);
#endif

#ifdef CAPABILITY_DELEGATING_CONSTRUCTOR
  DISPLAY_SUPPORTED(CAPABILITY_DELEGATING_CONSTRUCTOR);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_DELEGATING_CONSTRUCTOR);
#endif

#ifdef CAPABILITY_DELEGATING_CONSTRUCTOR
  DISPLAY_SUPPORTED(CAPABILITY_DEFAULTED_FUNCTIONS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_DEFAULTED_FUNCTIONS);
#endif

#ifdef CAPABILITY_DIGRAPHS
  DISPLAY_SUPPORTED(CAPABILITY_DIGRAPHS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_DIGRAPHS);
#endif

#ifdef CAPABILITY_GENERIC_LAMBDAS
  DISPLAY_SUPPORTED(CAPABILITY_GENERIC_LAMBDAS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_GENERIC_LAMBDAS);
#endif

#ifdef CAPABILITY_INITIALISER_LISTS
  DISPLAY_SUPPORTED(CAPABILITY_INITIALISER_LISTS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_INITIALISER_LISTS);
#endif

#ifdef CAPABILITY_RANGE_BASE_FOR
  DISPLAY_SUPPORTED(CAPABILITY_RANGE_BASE_FOR);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_RANGE_BASE_FOR);
#endif

#ifdef CAPABILITY_THREAD
  DISPLAY_SUPPORTED(CAPABILITY_THREAD);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_THREAD);
#endif

#ifdef CAPABILITY_THREAD_LOCAL_VARIABLES
  DISPLAY_SUPPORTED(CAPABILITY_THREAD_LOCAL_VARIABLES);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_THREAD_LOCAL_VARIABLES);
#endif

#ifdef CAPABILITY_TYPE_TRAITS
  DISPLAY_SUPPORTED(CAPABILITY_TYPE_TRAITS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_TYPE_TRAITS);
#endif

#ifdef CAPABILITY_USER_DEFINED_LITERALS
  DISPLAY_SUPPORTED(CAPABILITY_USER_DEFINED_LITERALS);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_USER_DEFINED_LITERALS);
#endif

#ifdef CAPABILITY_VARIADIC_TEMPLATES
  DISPLAY_SUPPORTED(CAPABILITY_VARIADIC_TEMPLATES);
#else
  DISPLAY_UNSUPPORTED(CAPABILITY_VARIADIC_TEMPLATES);
#endif
}
