//=============================================================================
// Accessing an element of an array via ptr[3] is actually just short for
// *(ptr + 3). This can be equivalently written as *(3 + ptr) and therefore
// as 3[ptr]

#include <iostream>

using namespace std;

//=============================================================================
int main() {
  int array[2] = {0,1};
  cout << array[0] << " " << 1[array] << endl;
  return 0;
}
