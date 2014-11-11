//=============================================================================

#ifndef Range_H
#define Range_H

#include "Capabilities.h"
#if CAPABILITY_DELEGATING_CONSTRUCTOR
#include "RangeIter.h"

//=============================================================================
template <typename T>
class Range {
public:

  Range(T end);
  // Makes a range [0, end)

  Range(T start, T end);
  // Makes a range [start, end)

  Range(T start, T end, T step);
  // Makes a range [start, end) with interval step.
  // e.g. Range<int>(2, 6, 2) yields {2, 4}

  ~Range();
  
  T operator()() const;

  void operator++();

  operator bool() const;

  RangeIter<T> begin();
  
  RangeIter<T> end();
  
private:

  const T m_start;
  const T m_end;
  const T m_step;
  T m_current;
};

//=============================================================================
template <typename T>
Range<T>::Range(T end)
  : Range(0, end, 1)
{
}

//=============================================================================
template <typename T>
Range<T>::Range(T start, T end)
  : Range(start, end, 1)
{
}

//=============================================================================
template <typename T>
Range<T>::Range(T start, T end, T step)
  : m_start(start),
    m_end(end),
    m_step(step),
    m_current(start)
{
}

//=============================================================================
template <typename T>
Range<T>::~Range()
{
}

//=============================================================================
template <typename T>
T Range<T>::operator()() const
{
  assert(*this);
  return m_current;
}

//=============================================================================
template <typename T>
void Range<T>::operator++()
{
  m_current += m_step;
}

//=============================================================================
template <typename T>
Range<T>::operator bool() const
{
  return m_current < m_end;
}

//=============================================================================
template <typename T>
RangeIter<T> Range<T>::begin()
{
  return RangeIter<T>(this);
}

//=============================================================================
template <typename T>
RangeIter<T> Range<T>::end()
{
  return RangeIter<T>(nullptr);
}

#else
#error "CAPABILITY_DELEGATING_CONSTRUCTOR"
#endif
#endif
