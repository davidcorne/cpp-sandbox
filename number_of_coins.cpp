//=============================================================================
//adapted from here
// http://stackoverflow.com/questions/1106929/find-all-combinations-of-coins-when-given-some-dollar-value


#include <iostream>

#include <stdlib.h>

//=============================================================================
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "usage: change amount-in-cents" << std::endl;
    return 1;
  }

  int total = atoi(argv[1]);

  std::cout << "quarter\tdime\tnickle\tpenny\tto make " << total << std::endl;

  int combos = 0;

  for (int quarters = 0; quarters <= total / 25; quarters++) {
    int total_less_quarters = total - quarters * 25;
    for (int dimes = 0; dimes <= total_less_quarters / 10; dimes++) {
      int total_less_quarters_dimes = total_less_quarters - dimes * 10;
      for (int nickles = 0; nickles <= total_less_quarters_dimes / 5; nickles++) {
        int pennies = total_less_quarters_dimes - nickles * 5;
        std::cout << quarters
             << "\t"
             << dimes
             << "\t"
             << nickles
             << "\t"
             << pennies
             << std::endl;
        combos++;
      }
    }
  }

  std::cout << combos << " combinations" << std::endl;

  return 0;
}
