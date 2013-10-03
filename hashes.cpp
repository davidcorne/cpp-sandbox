#include <iostream>

#define UT_JOIN(a, args...) a ## args
#pragma GCC diagnostic ignored "-Wunused-variable"

int main() {
  int ab = 2;
  int abc = 53;
  int cd = UT_JOIN(a, b, c);
  std::cout << cd << std::endl;
  return 0;
}
