#include "ContestedTypename.h"

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase()
  : m_current(nullptr)
{
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::NodeIteratorBase(
  tNODE_TYPE node
)
  : m_current(node)
{
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
  m_current = m_current->next;
  return *reinterpret_cast<tDERIVED_ITERATOR*>(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR& ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--()
{
  m_current = m_current->previous;
  // <nnn> 
  return *(tDERIVED_ITERATOR*)(this);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator++(int)
{
  tDERIVED_ITERATOR it = *this;
  m_current = m_current->next;
  return it;
}

//=============================================================================
template <typename tCONTAINS>
template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
tDERIVED_ITERATOR ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator--(int)
{
  tDERIVED_ITERATOR it = *this;
  m_current = m_current->previous;
  return it;
}
   
// <nnn> //=============================================================================
// <nnn> template <typename tCONTAINS>
// <nnn> template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
// <nnn> tCONTAINS& ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator*()
// <nnn> {
// <nnn>   return  NodeIteratorBase<NodeIteratorConst, const Node*>::m_current->value;
// <nnn> }

// <nnn> //=============================================================================
// <nnn> template <typename tCONTAINS>
// <nnn> template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
// <nnn> typename ArrayList<tCONTAINS>::template NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::pointer
// <nnn> ArrayList<tCONTAINS>::NodeIteratorBase<tDERIVED_ITERATOR, tNODE_TYPE>::operator->()
// <nnn> {
// <nnn>   return &m_current->value;
// <nnn> }
  
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
  return node() != a_it.node();
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
ArrayList<tCONTAINS>::NodeIterator::NodeIterator()
: NodeIteratorBase<NodeIterator, Node*>()
{
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::NodeIterator::NodeIterator(Node* node)
  : NodeIteratorBase<NodeIterator, Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::NodeIterator::operator typename ArrayList<tCONTAINS>::NodeIteratorConst() const
{
  return NodeIteratorConst(NodeIteratorBase<NodeIterator, Node*>::m_current);
}

//=============================================================================
template <typename tCONTAINS>
tCONTAINS& ArrayList<tCONTAINS>::NodeIterator::operator*()
{
  return  m_current->value;
}


//=============================================================================
template <typename tCONTAINS>
tCONTAINS* ArrayList<tCONTAINS>::NodeIterator::operator->()
{
  return  &m_current->value;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::NodeIteratorConst::NodeIteratorConst()
  : NodeIteratorBase<NodeIteratorConst, const Node*>()
{
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::NodeIteratorConst::NodeIteratorConst(const Node* node)
  : NodeIteratorBase<NodeIteratorConst, const Node*>(node)
{
}

//=============================================================================
template <typename tCONTAINS>
const tCONTAINS& ArrayList<tCONTAINS>::NodeIteratorConst::operator*()
{
  return  NodeIteratorBase<NodeIteratorConst, const Node*>::m_current->value;
}


//=============================================================================
template <typename tCONTAINS>
const tCONTAINS* ArrayList<tCONTAINS>::NodeIteratorConst::operator->()
{
  return  &NodeIteratorBase<NodeIteratorConst, const Node*>::m_current->value;
}
