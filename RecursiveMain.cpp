//
// 

#include <iostream>

static int COUNT = 0;

//=============================================================================
int main() {
  ++COUNT;
  std::cout << COUNT << std::endl;
  return main();
}
