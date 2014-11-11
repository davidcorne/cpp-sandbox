//
// 

#define RECURSIVE_ON_ALL_PATHS 1
#include "IgnoreDiagnostics.h"

#include <iostream>

static int COUNT = 0;

//=============================================================================
int main() {
  ++COUNT;
  std::cout << COUNT << std::endl;
  return main();
}
