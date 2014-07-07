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
#include "GenericIteratorWrapper.h"

//=============================================================================
namespace IteratorCreators {

  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container);
  
  template <typename CONTAINER>
  Iterator<typename CONTAINER::DGC_VALUE_TYPE> iter(CONTAINER& container);
  
}

//=============================================================================
namespace IteratorCreators {
  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container)
  {
    typedef typename CONTAINER::value_type T;
    std::unique_ptr<AbsIterator<T> > ptr(
      new STLIteratorWrapper<typename CONTAINER::iterator>(
        std::begin(container),
        std::end(container)
      )
    );
    Iterator<T> iter(std::move(ptr));
    return iter;
  }

  template <typename CONTAINER>
  Iterator<typename CONTAINER::DGC_VALUE_TYPE> iter(CONTAINER& container)
  {
    typedef typename CONTAINER::DGC_VALUE_TYPE T;
    std::unique_ptr<AbsIterator<T> > ptr(
      new GenericIteratorWrapper<CONTAINER>(container)
    );
    Iterator<T> iter(std::move(ptr));
    return iter;
  }
}

