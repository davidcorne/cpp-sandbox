//=============================================================================
// Made to test getenv from cstdlib for getting environmental variables.

#include <cstdlib>
#include <iostream>

int main()
// main function
{
  std::cout << getenv("ORTHO_MINI_CONNTECTED") << std::endl;
  return 0;
}
