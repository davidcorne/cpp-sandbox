//=============================================================================
// 
// Looking at a size finding 

#include <iostream>

int main() {
  int* dyn_array = new int[10];
  std::cout << "Size of pointer: " << sizeof(dyn_array) << std::endl;
  std::cout << "Size of int: " << sizeof(dyn_array[0]) << std::endl;
  // this returns 4, 4 (compiler depependent I think) so can't use
  // sizeof(array) / sizeof(array[0]) to determine length
  delete [] dyn_array;
  return 0;
}
