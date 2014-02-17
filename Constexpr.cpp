//=============================================================================
//
// 

#include "compiler_guards.h"

#include <iostream>
using namespace std;

#if CPP_ELEVEN_SUPPORTED
//=============================================================================
constexpr int return_one() {
  return 1;
}

//=============================================================================
int main() {
  cout << return_one() << endl;
  return 0;
}

#else
NOT_SUPPORTED_MAIN
#endif
