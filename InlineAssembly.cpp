//=============================================================================
//
//D To show some inline assembly.
//

#include <iostream>
#include <assert.h>

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
  std::cout << foo << " + " << bar << " = " << result << std::endl;
  assert(result == 25);
  return 0;
}
