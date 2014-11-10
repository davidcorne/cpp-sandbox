//=============================================================================

#ifndef STLIteratorWrapper_H
#define STLIteratorWrapper_H

#include "AbsIterator.h"
#include <UnitCpp/Test.h>

//=============================================================================
template <typename ITER>
class STLIteratorWrapper : public AbsIterator<typename ITER::value_type> {
public:

  typedef typename ITER::value_type CONTAINED;
  
  STLIteratorWrapper(const ITER& begin, const ITER& end);

  virtual ~STLIteratorWrapper();

  virtual std::unique_ptr<AbsIterator<CONTAINED> > clone() const override;
  
  virtual bool operator++() override;

  virtual typename ITER::value_type& operator()() override;

  virtual const CONTAINED& operator()() const override;

private:
  
  UNITCPP_FRIEND_TEST(STLIteratorWrapper, vector_iteration);

  const ITER m_begin;
  const ITER m_end;
  
  ITER m_iter;

};

//=============================================================================
template <typename ITER>
STLIteratorWrapper<ITER>::STLIteratorWrapper(
  const ITER& begin,
  const ITER& end
)
  : m_begin(begin),
    m_end(end),
    m_iter(end)
{
}

//=============================================================================
template <typename ITER>
STLIteratorWrapper<ITER>::~STLIteratorWrapper()
{
}

//=============================================================================
template <typename ITER>
std::unique_ptr<AbsIterator<typename ITER::value_type> >
  STLIteratorWrapper<ITER>::clone() const
{
  auto stl_iter = new STLIteratorWrapper<ITER>(m_begin, m_end);
  stl_iter->m_iter = m_iter;
  std::unique_ptr<AbsIterator<CONTAINED> > ptr(std::move(stl_iter));
  return std::move(ptr);
}

//=============================================================================
template <typename ITER>
bool STLIteratorWrapper<ITER>::operator++()
{
  if (m_iter == m_end) {
    m_iter = m_begin;
  } else {
    ++m_iter;
  }
  bool ok = m_iter != m_end;
  return ok;
}

//=============================================================================
template <typename ITER>
typename ITER::value_type& STLIteratorWrapper<ITER>::operator()()
{
  return *m_iter;
}

//=============================================================================
template <typename ITER>
const typename ITER::value_type& STLIteratorWrapper<ITER>::operator()() const
{
  return *m_iter;
}

#endif
