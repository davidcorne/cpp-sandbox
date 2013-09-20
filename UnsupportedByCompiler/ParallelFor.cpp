// parallel-for-structure.cpp 
// compile with: /EHsc
#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>

using namespace Concurrency;
using namespace std;

//=============================================================================
void print(int val) {
  cout << val << endl;
}

//=============================================================================
int main()
{
   // Print each value from 1 to 5 in parallel.
  parallel_for(1, 6, print);
}

// <nnn> //
// <nnn> // 

// <nnn> #include <iostream>
// <nnn> #include <ppl.h>
// <nnn> using namespace std;

// <nnn> int main() {
// <nnn>   concurrency::parallel_for(1, 6, [](int value) {
// <nnn>       cout 
// <nnn>     }
// <nnn>   return 0;
// <nnn> }
