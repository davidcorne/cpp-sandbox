//=============================================================================

#ifndef GenericIteratorWrapper_H
#define GenericIteratorWrapper_H

#include "AbsIterator.h"

//=============================================================================
template <typename CONTAINER>
class GenericIteratorWrapper :
  public AbsIterator<typename CONTAINER::DGC_VALUE_TYPE>
{
public:

  typedef typename CONTAINER::DGC_VALUE_TYPE CONTAINED;
  
  GenericIteratorWrapper(CONTAINER& container);

  virtual ~GenericIteratorWrapper();

  virtual std::unique_ptr<AbsIterator<CONTAINED> > clone() const override;
  
  virtual bool operator++() override;

  virtual CONTAINED& operator()() override;

  virtual const CONTAINED& operator()() const override;

private:

  GenericIteratorWrapper(CONTAINER& container, int position);

  friend class utest_GenericIteratorWrapper;

  CONTAINER& m_container;
  int m_pos;
};

//=============================================================================
template <typename CONTAINER>
GenericIteratorWrapper<CONTAINER>::GenericIteratorWrapper(
  CONTAINER& container,
  int position
)
  : m_container(container),
    m_pos(position)
{
}

//=============================================================================
template <typename CONTAINER>
GenericIteratorWrapper<CONTAINER>::GenericIteratorWrapper(
  CONTAINER& container
)
  : m_container(container),
    m_pos(-1)
{
}

//=============================================================================
template <typename CONTAINER>
GenericIteratorWrapper<CONTAINER>::~GenericIteratorWrapper()
{
}

//=============================================================================
template <typename CONTAINER>
std::unique_ptr<AbsIterator<typename CONTAINER::DGC_VALUE_TYPE> >
  GenericIteratorWrapper<CONTAINER>::clone() const
{
  std::unique_ptr<AbsIterator<CONTAINED> > ptr(
    new GenericIteratorWrapper<CONTAINER>(m_container, m_pos)
  );
  return std::move(ptr);
}

//=============================================================================
template <typename CONTAINER>
bool GenericIteratorWrapper<CONTAINER>::operator++()
{
  ++m_pos;
  return m_pos < m_container.size();
}

//=============================================================================
template <typename CONTAINER>
typename CONTAINER::DGC_VALUE_TYPE& GenericIteratorWrapper<CONTAINER>::operator()()
{
  return m_container[m_pos];
}

//=============================================================================
template <typename CONTAINER>
const typename CONTAINER::DGC_VALUE_TYPE& GenericIteratorWrapper<CONTAINER>::operator()() const
{
  return m_container[m_pos];
}

#endif
