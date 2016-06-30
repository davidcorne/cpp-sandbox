//=============================================================================
// This shows how you sleep a C++ program in a platform independent way

#include "Capabilities.h"
#ifdef CAPABILITY_THREAD

#include "Sleep.h"
#include "Sleep.h"

#include <iostream>

//=============================================================================
int main()
{
  std::cout << "Starting program, will sleep for 1 second." << std::endl;
  DGC::sleep(1);
  std::cout << "End." << std::endl;
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_THREAD)
#endif
