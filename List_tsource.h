#include <limits>

//----- List

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::List()
{
  m_sentinel = {tCONTAINS(), nullptr, nullptr};
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::List(std::initializer_list<tCONTAINS> init)
  : List()
{
  Node* current = &m_sentinel;
  for (const tCONTAINS& contains : init) {
    Node* new_node = new Node{contains, current, nullptr};
    current->next = new_node;
    current = new_node;
  }
  m_sentinel.previous = current;
  current->next = &m_sentinel;
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::~List()
{
  // Clear the list, so the memory is deleted.
  clear();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::size_type List<tCONTAINS>::size() const
{
  size_type count{0};
  for (const auto& i : *this) {
    ++count;
  }
  return count;
}

//=============================================================================
template <typename tCONTAINS>
bool List<tCONTAINS>::empty() const
{
  // If there's no first node, it's empty.
  return !m_sentinel.next;
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::size_type List<tCONTAINS>::max_size() const
{
  return std::numeric_limits<size_type>::max();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::reference List<tCONTAINS>::front()
{
  return m_sentinel.next->value;
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reference List<tCONTAINS>::front() const
{
  return m_sentinel.next->value;
}
 
//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::reference List<tCONTAINS>::back()
{
  return m_sentinel.previous->value;
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reference List<tCONTAINS>::back() const
{
  return m_sentinel.previous->value;
}
 
//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::clear()
{
  Node* current = m_sentinel.next;
  while (current && current != &m_sentinel) {
    Node* to_delete = current;
    current = to_delete->next;
    to_delete->next = nullptr;
    to_delete->previous = nullptr;
    delete to_delete;
  }
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::insert(
  const_iterator position,
  const tCONTAINS& value
)
{
  Node* node = const_cast<Node*>(position.node());
  Node* old_next = node->next;
  node->next = new Node{value, node, old_next};
  assert(old_next && "Shouldn't get any null nodes.");
  old_next->previous = node->next;
  return iterator(node->next);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::erase(
  const_iterator position
)
{
  Node* node = const_cast<Node*>(position.node());
  Node* previous = node->previous;
  Node* next = node->next;
  assert(previous && next && "There should be all valid nodes.");
  if (previous == next) {
    // the list is now empty
    m_sentinel.next = nullptr;
    m_sentinel.previous = nullptr;
  } else {
    previous->next = next;
    next->previous = previous;
  }
  delete node;
  return iterator(next);
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::push_back(const tCONTAINS& value)
{
  Node* node = new Node{value, nullptr, nullptr};
  if (empty()) {
    m_sentinel.next = node;
    m_sentinel.previous = node;
    node->next = &m_sentinel;
    node->previous = &m_sentinel;
  } else {
    
  }
  assert(node->previous && node->next && "Next or previous shouldn't be null.");
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::push_front(const tCONTAINS& value)
{
  Node* old_front = m_sentinel.next;
  m_sentinel.next = new Node{value, &m_sentinel, old_front};
  if (old_front) {
    old_front->previous = m_sentinel.next;
  } else {
    m_sentinel.next->previous = &m_sentinel;
  }
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::pop_back()
{
  erase(--end());
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::pop_front()
{
  erase(begin());
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::begin()
{
  return NodeIterator(m_sentinel.next);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::begin() const
{
  return NodeIteratorConst(m_sentinel.next);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::end()
{
  return NodeIterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::end() const
{
  return NodeIteratorConst(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::cbegin() const
{
  return NodeIteratorConst(m_sentinel.next);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::cend() const
{
  return NodeIteratorConst(&m_sentinel);
}

template <typename tCONTAINS>
typename List<tCONTAINS>::iterator begin(List<tCONTAINS>& list)
{
  return list.begin();
}

template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator begin(const List<tCONTAINS>& list)
{
  return list.begin();
}

template <typename tCONTAINS>
typename List<tCONTAINS>::iterator end(List<tCONTAINS>& list)
{
  return list.end();
}

template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator end(const List<tCONTAINS>& list)
{
  return list.end();
}

template <typename tCONTAINS>
bool operator==(const List<tCONTAINS>& lhs, const List<tCONTAINS>& rhs)
{
  bool ret_val = lhs.size() == rhs.size();
  if (ret_val) {
    auto l = begin(lhs);
    auto r = begin(rhs);
    while (l != end(lhs) && r != end(rhs)) {
      if (!(*l == *r)) {
        ret_val = false;
        break;
      }
      ++l;
      ++r;
    }
  }
  return ret_val;
}

template <typename tCONTAINS>
bool operator!=(const List<tCONTAINS>& lhs, const List<tCONTAINS>& rhs)
{
  return !(lhs == rhs);
}

