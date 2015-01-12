//=============================================================================
// This shows how you sleep a C++ program in a platform independent way

#include "Capabilities.h"
#ifdef CAPABILITY_THREAD
#include <thread>
#include <chrono>
#include <iostream>

//=============================================================================
int main()
{
  std::cout << "Starting program, will sleep for 1 second." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "End." << std::endl;
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_THREAD)
#endif
