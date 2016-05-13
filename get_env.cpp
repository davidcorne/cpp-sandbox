//=============================================================================
// Made to test getenv from cstdlib for getting environmental variables.

#include "dgc_getenv.h"

#include <iostream>

int main()
// main function
{
  auto pair = DGC::getenv("ORTHO_MINI_CONNTECTED");
  std::cout
    << "ORTHO_MINI_CONNTECTED"
    << "\n"
    << "set: "
    << std::boolalpha
    << pair.first
    << "\n"
    << "value: "
    << pair.second
    << std::endl;
  return 0;
}
