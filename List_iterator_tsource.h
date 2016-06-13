#include "ContestedTypename.h"

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase(
  tNODE_TYPE node
)
  : m_current(node)
{
}
    
//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase(
  const CONTESTED_TYPENAME List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>&
)
= default;

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
CONTESTED_TYPENAME List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>& List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator=(
  const CONTESTED_TYPENAME List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>&
)
= default;

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++()
{
  increment();
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--()
{
  decrement();
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++(int)
{
  tDERIVED_ITERATOR it = *this;
  increment();
  return it;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--(int)
{
  tDERIVED_ITERATOR it = *this;
  decrement();
  return it;
}
   
//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
bool List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator==(
  const tDERIVED_ITERATOR& a_it
) const
{
  return node() == a_it.node();
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
bool List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator!=(
  const tDERIVED_ITERATOR& a_it
) const
{
  return !(*this == a_it);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tNODE_TYPE List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::node() const
{
  return m_current;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
List<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::NodeIterator(Node* node)
  : NodeIteratorBase<tDERIVED_ITERATOR, Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
tCONTAINS& List<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::operator*()
{
  return  m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
tCONTAINS* List<tCONTAINS>::NodeIterator<tDERIVED_ITERATOR>::operator->()
{
  return  &m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
List<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::NodeIteratorConst(const Node* node)
  : NodeIteratorBase<tDERIVED_ITERATOR, const Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
const tCONTAINS& List<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::operator*()
{
  return  NodeIteratorBase<tDERIVED_ITERATOR, const Node*>::m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR>
const tCONTAINS* List<tCONTAINS>::NodeIteratorConst<tDERIVED_ITERATOR>::operator->()
{
  return  &NodeIteratorBase<tDERIVED_ITERATOR, const Node*>::m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::ForwardNodeIterator::ForwardNodeIterator(Node* node)
: NodeIterator<ForwardNodeIterator>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::ForwardNodeIterator::increment()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::ForwardNodeIterator::decrement()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::ForwardNodeIterator::operator typename List<tCONTAINS>::ForwardNodeIteratorConst() const
{
  return ForwardNodeIteratorConst(
    NodeIteratorBase<ForwardNodeIterator, Node*>::m_current
  );
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::BackwardNodeIterator::BackwardNodeIterator(Node* node)
: NodeIterator<BackwardNodeIterator>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::BackwardNodeIterator::increment()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::BackwardNodeIterator::decrement()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::BackwardNodeIterator::operator typename List<tCONTAINS>::BackwardNodeIteratorConst() const
{
  return BackwardNodeIteratorConst(
    NodeIteratorBase<BackwardNodeIterator, Node*>::m_current
  );
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::ForwardNodeIteratorConst::ForwardNodeIteratorConst(
  const Node* node
)
: NodeIteratorConst<ForwardNodeIteratorConst>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::ForwardNodeIteratorConst::increment()
{
  m_current = m_current->next;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::ForwardNodeIteratorConst::decrement()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::BackwardNodeIteratorConst::BackwardNodeIteratorConst(
  const Node* node
)
: NodeIteratorConst<BackwardNodeIteratorConst>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::BackwardNodeIteratorConst::increment()
{
  m_current = m_current->previous;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::BackwardNodeIteratorConst::decrement()
{
  m_current = m_current->next;
}
