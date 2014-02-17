#include "compiler_guards.h"

#include <iostream>
#if CPP_ELEVEN_SUPPORTED
int main() {
  std::cout << "C++11 supported" << std::endl;
}
#else
NOT_SUPPORTED_MAIN
#endif
