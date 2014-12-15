//=============================================================================
#ifndef Enumeration_H
#define Enumeration_H

#include "EnumerationIterator.h"

//=============================================================================
template <typename CONTAINER>
class Enumeration {
public:

  Enumeration(const CONTAINER& container);

  EnumerationIterator<CONTAINER> begin();
  
  EnumerationIterator<CONTAINER> end();      
  
  Enumeration(const Enumeration&) = default;
  Enumeration& operator=(const Enumeration&) = default;
  
private:

  friend class utest_Enumeration;
  const CONTAINER* m_container;
};

//=============================================================================
template <typename CONTAINER>
Enumeration<CONTAINER> make_enumeration(const CONTAINER& container);

//=============================================================================
template <typename CONTAINER>
Enumeration<CONTAINER>::Enumeration(const CONTAINER& container)
  : m_container(&container)
{
}

//=============================================================================
template <typename CONTAINER>
EnumerationIterator<CONTAINER> Enumeration<CONTAINER>::begin()
{
  return EnumerationIterator<CONTAINER>(
    std::begin(*m_container),
    std::end(*m_container),
    std::begin(*m_container),
    0
  );
}

//=============================================================================
template <typename CONTAINER>
EnumerationIterator<CONTAINER> Enumeration<CONTAINER>::end()
{
  return EnumerationIterator<CONTAINER>(
    std::begin(*m_container),
    std::end(*m_container),
    std::end(*m_container),
    m_container->size()
  );
}

//=============================================================================
template <typename CONTAINER>
Enumeration<CONTAINER> make_enumeration(const CONTAINER& container)
{
  return Enumeration<CONTAINER>(container);
}


#endif
