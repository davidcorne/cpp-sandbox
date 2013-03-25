//adapted from here
// http://stackoverflow.com/questions/1106929/find-all-combinations-of-coins-when-given-some-dollar-value

#include <iostream>

#include <stdlib.h>

// not hurting anyone here
using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cout << "usage: change amount-in-cents" << endl;
    return 1;
  }

  int total = atoi(argv[1]);

  cout << "quarter\tdime\tnickle\tpenny\tto make " << total << endl;

  int combos = 0;

  for (int quarters = 0; quarters <= total / 25; quarters++) {
    int total_less_quarters = total - quarters * 25;
    for (int dimes = 0; dimes <= total_less_quarters / 10; dimes++) {
      int total_less_quarters_dimes = total_less_quarters - dimes * 10;
      for (int nickles = 0; nickles <= total_less_quarters_dimes / 5; nickles++) {
        int pennies = total_less_quarters_dimes - nickles * 5;
        cout << quarters
             << "\t"
             << dimes
             << "\t"
             << nickles
             << "\t"
             << pennies
             << endl;
        combos++;
      }
    }
  }

  cout << combos << " combinations" << endl;

  return 0;
}
