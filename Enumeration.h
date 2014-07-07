//=============================================================================
#ifndef Enumeration_H
#define Enumeration_H

#include "EnumerationIterator.h"

//=============================================================================
template<typename CONTAINER>
class Enumeration {
public:

  Enumeration(const CONTAINER& array)
    : m_array(array)
    {}

  EnumerationIterator<CONTAINER> begin() {
    return EnumerationIterator<CONTAINER>(
      std::begin(m_array),
      std::end(m_array),
      std::begin(m_array),
      0
    );
  }
  
  EnumerationIterator<CONTAINER> end() {
    return EnumerationIterator<CONTAINER>(
      std::begin(m_array),
      std::end(m_array),
      std::end(m_array),
      m_array.size()
    );
  }
      
  
private:
  friend class utest_Enumeration;
  const CONTAINER& m_array;
};



#endif
