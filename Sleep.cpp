//=============================================================================
// This shows how you sleep a C++ program in a platform independent way

#include <thread>
#include <chrono>

#include "Printer.h"

//=============================================================================
int main()
{
  Printer printer(std::cout);
  printer.print("Starting program, will sleep for 1 second.");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  printer.print("End.");
  return 0;
}
