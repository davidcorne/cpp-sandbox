//=============================================================================
// 
// Looking at a size finding 

#include <iostream>

using namespace std;

int main() {
  int* dyn_array = new int[10];
  cout << "Size of pointer: " << sizeof(dyn_array) << endl;
  cout << "Size of int: " << sizeof(dyn_array[0]) << endl;
  // this returns 4, 4 (compiler depependent I think) so can't use
  // sizeof(array) / sizeof(array[0]) to determine length
  delete [] dyn_array;
  return 0;
}
