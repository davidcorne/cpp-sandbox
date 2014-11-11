//to see if dividing by zero compiles

#define UNUSED_VARIABLE
#include "IgnoreDiagnostics.h"

int main()
// main function
{
  int zero = 0;
  // no warning
  double infinity = 1 / zero;

  const int const_zero = 0;
  // warning (now an error due to -Werror)
  // <nnn> infinity = 1 / const_zero;

  // warning (now an error due to -Werror)
  // <nnn> infinity = 1 / 0;
return 0;
}
