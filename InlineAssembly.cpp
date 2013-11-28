//=============================================================================
//
//D To show some inline assembly.
//

#include <iostream>
#include <assert.h>

using namespace std;

//=============================================================================
int main(void)
{
  int result;
  int foo = 10;
  int bar = 15;
  __asm__ __volatile__("addl  %%ebx,%%eax"
                       :"=a"(result)
                       :"a"(foo), "b"(bar)
  );
  cout << foo << " + " << bar << " = " << result << endl;
  assert(result == 25);
  return 0;
}
