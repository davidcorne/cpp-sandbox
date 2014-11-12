//=============================================================================

#include "Capabilities.h"
#if CAPABILITY_INITIALISER_LISTS
#include <iostream>


//=============================================================================
bool is_prime(int number, int c=2)
{
  if (number <= 1) return false;
  return (c*c > number) ? true : (number % c == 0) ? false : is_prime(number, c + 1);
}



//=============================================================================
int main()
{
  std::cout << std::boolalpha;
  for (auto num: {2, 3, 4, 1000000001}) {
    std::cout << num << ": " << is_prime(num) << "\n";
  }
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif
