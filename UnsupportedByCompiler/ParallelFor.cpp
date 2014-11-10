// parallel-for-structure.cpp 
// compile with: /EHsc
#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>
#include <vector>

//=============================================================================
void print(std::vector<int>& v) {
  for (auto i = begin(v); i != end(v); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}

//=============================================================================
int main()
{
   // Print each value from 1 to 5 in parallel.
  std::vector<int> points(5, 0);
  print(points);
  Concurrency::parallel_for(0, 5, [&points](int i) {
      points[i] = i;
      std::cout << i << " ";
    });
  std::cout << std::endl;
  print(points);
  
}
