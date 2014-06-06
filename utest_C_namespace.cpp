#include "C_namespace.h"

int main() {
  C::printf("in a namespace.\n");
  // printf("no namespace.\n"); // won't compile
  return 0;
}
