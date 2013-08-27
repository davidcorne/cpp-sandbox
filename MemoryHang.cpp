//
//

#include <iostream>

using namespace std;

//=============================================================================
void allocate()
{
  while (true) {
    int* i = new int[100];
  }
}

//=============================================================================
int main()
{
  allocate();
  return 0;
}
