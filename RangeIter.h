//=============================================================================

#ifndef RangeIter_H
#define RangeIter_H

#include <cassert>

template <typename T>
class Range;

//=============================================================================
template <typename T>
class RangeIter {
public:

  RangeIter(Range<T>* range);
  
  ~RangeIter();

  void operator++();
  
  T operator*();

  template <typename U>
  friend bool operator==(const RangeIter<U>& first, const RangeIter<U>& other);

private:

  // <nnn> template <typename T>
  // <nnn> friend bool operator==(const RangeIter<T>& first, const RangeIter<T>& other);
  
  Range<T>* m_range;
  
};

template <typename T>
bool operator!=(const RangeIter<T>& first, const RangeIter<T>& second);

template <typename T>
bool operator==(const RangeIter<T>& first, const RangeIter<T>& second);

//=============================================================================
template <typename T>
RangeIter<T>::RangeIter(Range<T>* range)
  : m_range(range)
{
}

//=============================================================================
template <typename T>
RangeIter<T>::~RangeIter()
{
}

//=============================================================================
template <typename T>
void RangeIter<T>::operator++()
{
  assert(m_range);
  ++(*m_range);
}

//=============================================================================
template <typename T>
T RangeIter<T>::operator*()
{
  assert(m_range);
  return (*m_range)();
}

//=============================================================================
template <typename T>
bool operator==(const RangeIter<T>& first, const RangeIter<T>& second)
{
  if (!first.m_range && !second.m_range) {
    // Both pointer bad.
    return true;
  }
  if (first.m_range == second.m_range) {
    // Pointers equal.
    return true;
  }
  if (!first.m_range) {
    // first m_range bad.
    Range<T>& range = *second.m_range;
    return !range;
  }
  if (second.m_range == nullptr) {
    // second m_range bad.
    Range<T>& range = *first.m_range;
    return !range;
  }
  // should never get here
  assert(false);
  return false;
}

//=============================================================================
template <typename T>
bool operator!=(const RangeIter<T>& first, const RangeIter<T>& second)
{
  return !(first == second);
}

#endif
