//=============================================================================
//
//D To show some inline assembly.
//

#include "Compiler.h"
#if COMPILER_TYPE != COMPILER_TYPE_VS

#include <iostream>
#include <cassert>

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

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN(COMPILER_TYPE_VS)
#endif
