//=============================================================================

#ifndef Iterator_H
#define Iterator_H

#include "AbsIterator.h"

//=============================================================================
template<typename T>
class Iterator {
public:

  Iterator(std::unique_ptr<AbsIterator<T> > iter);

  ~Iterator();

  Iterator(const Iterator& iter);

  Iterator& operator=(const Iterator& iter);

  bool operator++();

  T& operator()();

  const T& operator()() const;
  
private:

  std::unique_ptr<AbsIterator<T> > m_iter;

};

//=============================================================================
template <typename T>
Iterator<T>::Iterator(std::unique_ptr<AbsIterator<T> > iter)
  : m_iter(std::move(iter))
{
}

//=============================================================================
template <typename T>
Iterator<T>::~Iterator()
{
}

//=============================================================================
template <typename T>
Iterator<T>::Iterator(const Iterator<T>& iter)
  : m_iter(std::move(iter.m_iter->clone()))
{
}

//=============================================================================
template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iter)
{
  m_iter = iter.m_iter->clone();
  return *this;
}

//=============================================================================
template <typename T>
bool Iterator<T>::operator++()
{
  return m_iter->operator++();
}

//=============================================================================
template <typename T>
T& Iterator<T>::operator()()
{
  return m_iter->operator()();
}

//=============================================================================
template <typename T>
const T& Iterator<T>::operator()() const
{
  return m_iter->operator()();
}


#endif
