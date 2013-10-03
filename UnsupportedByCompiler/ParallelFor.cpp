// parallel-for-structure.cpp 
// compile with: /EHsc
#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>
#include <vector>

using namespace Concurrency;
using namespace std;

//=============================================================================
void print(vector<int>& v) {
  for (auto i = begin(v); i != end(v); ++i) {
    cout << *i << " ";
  }
  cout << endl;
}

//=============================================================================
int main()
{
   // Print each value from 1 to 5 in parallel.
  vector<int> points(5, 0);
  print(points);
  parallel_for(0, 5, [&points](int i) {
      points[i] = i;
      cout << i << " ";
    });
  cout << endl;
  print(points);
  
}
