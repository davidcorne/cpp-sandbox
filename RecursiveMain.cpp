//
// 

#include <iostream>
using namespace std;

static int COUNT = 0;

//=============================================================================
int main() {
  ++COUNT;
  cout << COUNT << endl;
  main();
  return 0;
}
