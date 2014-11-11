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
  DISPLAY_MACRO(CAPABILITY_DIGRAPHS);
  DISPLAY_MACRO(CAPABILITY_GENERIC_LAMBDAS);
  DISPLAY_MACRO(CAPABILITY_THREAD_LOCAL_VARIABLES);
  DISPLAY_MACRO(CAPABILITY_VARIADIC_TEMPLATES);
}
