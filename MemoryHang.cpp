//
//

#include <iostream>

using namespace std;

//=============================================================================
void allocate()
{
  while (true) {
    int* i = new int[100];
    i[0] = 0;
  }
}

//=============================================================================
int main()
{
  allocate();
  return 0;
}
