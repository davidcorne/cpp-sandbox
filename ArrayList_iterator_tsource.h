#include "ContestedTypename.h"

#include <cassert>

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase(
  tNODE_TYPE node
)
  : m_current(node)
{
  assert(node && "node shouldn't be null.");
}
    
//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase(
  const CONTESTED_TYPENAME ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>&
)
= default;

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
CONTESTED_TYPENAME ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>& ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator=(
  const CONTESTED_TYPENAME ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>&
)
= default;

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++()
{
  increment();
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--()
{
  decrement();
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++(int)
{
  tDERIVED_ITERATOR it = *this;
  increment();
  return it;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--(int)
{
  tDERIVED_ITERATOR it = *this;
  decrement();
  return it;
}
   
//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
bool ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator==(
  const tDERIVED_ITERATOR& a_it
) const
{
  return node() == a_it.node();
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
bool ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator!=(
  const tDERIVED_ITERATOR& a_it
) const
{
  return !(*this == a_it);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tNODE_TYPE ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::node() const
{
  return m_current;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
ArrayList<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::NodeIterator(Node* node)
  : NodeIteratorBase<tDERIVED_ITERATOR, Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
tCONTAINS& ArrayList<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::operator*()
{
  return  m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
tCONTAINS* ArrayList<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::operator->()
{
  return  &m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
ArrayList<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::NodeIteratorConst(const Node* node)
  : NodeIteratorBase<tDERIVED_ITERATOR, const Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
const tCONTAINS& ArrayList<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::operator*()
{
  return  NodeIteratorBase<tDERIVED_ITERATOR, const Node*>::m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
const tCONTAINS* ArrayList<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::operator->()
{
  return  &NodeIteratorBase<tDERIVED_ITERATOR, const Node*>::m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ForwardNodeIterator::ForwardNodeIterator(Node* node)
: NodeIterator<ForwardNodeIterator>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::ForwardNodeIterator::increment()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::ForwardNodeIterator::decrement()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ForwardNodeIterator::operator typename ArrayList<tCONTAINS>::ForwardNodeIteratorConst() const
{
  return ForwardNodeIteratorConst(
    NodeIteratorBase<ForwardNodeIterator, Node*>::m_current
  );
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::BackwardNodeIterator::BackwardNodeIterator(Node* node)
: NodeIterator<BackwardNodeIterator>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::BackwardNodeIterator::increment()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::BackwardNodeIterator::decrement()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::BackwardNodeIterator::operator typename ArrayList<tCONTAINS>::BackwardNodeIteratorConst() const
{
  return BackwardNodeIteratorConst(
    NodeIteratorBase<BackwardNodeIterator, Node*>::m_current
  );
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ForwardNodeIteratorConst::ForwardNodeIteratorConst(
  const Node* node
)
: NodeIteratorConst<ForwardNodeIteratorConst>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::ForwardNodeIteratorConst::increment()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::ForwardNodeIteratorConst::decrement()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::BackwardNodeIteratorConst::BackwardNodeIteratorConst(
  const Node* node
)
: NodeIteratorConst<BackwardNodeIteratorConst>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::BackwardNodeIteratorConst::increment()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::BackwardNodeIteratorConst::decrement()
{
  m_current = m_current->next;
}
