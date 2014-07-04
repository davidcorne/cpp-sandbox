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

