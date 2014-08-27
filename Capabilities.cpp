//=============================================================================
//
// Prints out the capabilities of the current compiler.

#include <iostream>
#include "Capabilities.h"

//=============================================================================
int main() {
  std::cout
    << "Variadic templates "
#ifndef VARIADIC_TEMPLATES
    << "not "
#endif // VARIADIC_TEMPLATES
    << "supported."
    << std::endl;
}
