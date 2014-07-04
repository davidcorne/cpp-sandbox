//=============================================================================
// Getting from generic STL iterators to iterators you can do this:
//
// Iterator<int> iter = container.iter();
// while (++iter) {
//   iter() += 5;
// }

#include "IteratorCreators.h"

//=============================================================================
int main()
{
  std::vector<int> array;
  array.push_back(0);
  array.push_back(1);
  array.push_back(2);
  array.push_back(3);
  array.push_back(4);
  
  Iterator<int> iter_1 = IteratorCreators::iter(array);
  while (++iter_1) {
    std::cout << iter_1() << std::endl;
  }
  
  Iterator<int> iter_2 = IteratorCreators::iter(array);
  while (++iter_2) {
    iter_2() += 1;
  }
  
  std::cout << std::endl;
  
  Iterator<int> iter_3 = IteratorCreators::iter(array);
  while (++iter_3) {
    std::cout << iter_3() << std::endl;
  }
  
  return 0;
}

