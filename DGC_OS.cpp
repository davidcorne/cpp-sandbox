//=============================================================================
// Print if we in a windows development environment.

#include "DGC_OS.h"
#include <iostream>

//=============================================================================
int main()
{
  std::cout << "Are we on windows: " << DGC_WINDOWS_DEV << std::endl;
  return 0;    
}
