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
  m_current = m_current->next;
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--()
{
  m_current = m_current->previous;
  // <nnn> 
  return *(tDERIVED_ITERATOR*)(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++(int)
{
  tDERIVED_ITERATOR it = *this;
  m_current = m_current->next;
  return it;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR List<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--(int)
{
  tDERIVED_ITERATOR it = *this;
  m_current = m_current->previous;
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
List<tCONTAINS>::NodeIterator::NodeIterator(Node* node)
  : NodeIteratorBase<NodeIterator, Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::NodeIterator::operator typename List<tCONTAINS>::NodeIteratorConst() const
{
  return NodeIteratorConst(NodeIteratorBase<NodeIterator, Node*>::m_current);
}

//=============================================================================
template <typename tCONTAINS>
tCONTAINS& List<tCONTAINS>::NodeIterator::operator*()
{
  return  m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
tCONTAINS* List<tCONTAINS>::NodeIterator::operator->()
{
  return  &m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::NodeIteratorConst::NodeIteratorConst(const Node* node)
  : NodeIteratorBase<NodeIteratorConst, const Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
const tCONTAINS& List<tCONTAINS>::NodeIteratorConst::operator*()
{
  return  NodeIteratorBase<NodeIteratorConst, const Node*>::m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
const tCONTAINS* List<tCONTAINS>::NodeIteratorConst::operator->()
{
  return  &NodeIteratorBase<NodeIteratorConst, const Node*>::m_current->value;
}
