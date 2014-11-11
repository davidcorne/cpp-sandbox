//=============================================================================
// Made to test getenv from cstdlib for getting environmental variables.

// getenv is depricated in visual studio.
#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>

int main()
// main function
{
  std::cout << getenv("ORTHO_MINI_CONNTECTED") << std::endl;
  return 0;
}
