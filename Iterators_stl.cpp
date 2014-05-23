//=============================================================================
// Getting from generic STL iterators to iterators you can do this:
//
// Iterator<int> iter = container.iter();
// while (++iter) {
//   iter() += 5;
// }

#include <assert.h>
#include <iostream>
#include <vector>
#include <memory>

#include "AbsIterator.h"
#include "Iterator.h"
#include "STLIteratorWrapper.h"

//=============================================================================
namespace IteratorCreators {

  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container);
  
}

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

//=============================================================================
namespace IteratorCreators {
  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container)
  {
    typedef typename CONTAINER::value_type T;
    AbsIterator<T>* abs_iter =
      new STLIteratorWrapper<typename CONTAINER::iterator>(
        std::begin(container),
        std::end(container)
      );
    std::unique_ptr<AbsIterator<T> > ptr(abs_iter);
    
    Iterator<T> iter(std::move(ptr));
    return iter;
  }
}

