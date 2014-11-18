//=============================================================================
//
// Prints out the capabilities of the current compiler.

#include <iostream>
#include <iomanip>
#include "Capabilities.h"

#define DISPLAY_MACRO(name)\
  std::cout << "Feature: " << std::left << std::setw(35) << #name << " " << (name ? "enabled" : "disabled") << std::endl

//=============================================================================
int main() {
  DISPLAY_MACRO(CAPABILITY_ATOMICS);
  DISPLAY_MACRO(CAPABILITY_CONSTEXPR);
  DISPLAY_MACRO(CAPABILITY_DELEGATING_CONSTRUCTOR);
  DISPLAY_MACRO(CAPABILITY_DEFAULTED_FUNCTIONS);
  DISPLAY_MACRO(CAPABILITY_DIGRAPHS);
  DISPLAY_MACRO(CAPABILITY_GENERIC_LAMBDAS);
  DISPLAY_MACRO(CAPABILITY_INITIALISER_LISTS);
  DISPLAY_MACRO(CAPABILITY_RANGE_BASE_FOR);
  DISPLAY_MACRO(CAPABILITY_THREAD);
  DISPLAY_MACRO(CAPABILITY_THREAD_LOCAL_VARIABLES);
  DISPLAY_MACRO(CAPABILITY_TYPE_TRAITS);
  DISPLAY_MACRO(CAPABILITY_USER_DEFINED_LITERALS);
  DISPLAY_MACRO(CAPABILITY_VARIADIC_TEMPLATES);
}
