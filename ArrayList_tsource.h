#include <limits>
#include <functional>

//----- ArrayList

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList()
{
  m_sentinel = {tCONTAINS(), nullptr, nullptr};
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList(std::initializer_list<tCONTAINS> init)
  : ArrayList()
{
  assign(init.begin(), init.end());
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList(const ArrayList<tCONTAINS>& list)
  : ArrayList()
{
  assign(list.begin(), list.end());
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>& ArrayList<tCONTAINS>::operator=(const ArrayList<tCONTAINS>& list)
{
  assign(list.begin(), list.end());
  return *this;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList(ArrayList<tCONTAINS>&& list)
  : ArrayList()
{
  *this = std::move(list);
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>& ArrayList<tCONTAINS>::operator=(
  ArrayList<tCONTAINS>&& list
)
{
  m_sentinel = list.m_sentinel;
  m_storage = std::move(list.m_storage);
  if (!m_storage.empty()) {
    m_storage.front().previous = &m_sentinel;
    m_storage.back().next = &m_sentinel;
  } else {
    assert(!m_sentinel.next && !m_sentinel.previous && "Links should be null");
  }
  return *this;
}

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::~ArrayList()
{
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::size_type ArrayList<tCONTAINS>::size() const
{
  return m_storage.size();
}

//=============================================================================
template <typename tCONTAINS>
bool ArrayList<tCONTAINS>::empty() const
{
  return m_storage.empty();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::size_type ArrayList<tCONTAINS>::max_size() const
{
  return m_storage.max_size();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::reference ArrayList<tCONTAINS>::front()
{
  return m_sentinel.next->value;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reference ArrayList<tCONTAINS>::front() const
{
  return m_sentinel.next->value;
}
 
//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::reference ArrayList<tCONTAINS>::back()
{
  return m_sentinel.previous->value;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reference ArrayList<tCONTAINS>::back() const
{
  return m_sentinel.previous->value;
}
 
//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::clear()
{
  m_storage.clear();
  m_sentinel.next = nullptr;
  m_sentinel.previous = nullptr;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::insert(
  const_iterator position,
  const tCONTAINS& value
)
{
  Node* node = const_cast<Node*>(position.node());
  assert(node && "Shouldn't get an iterator pointing at null.");
  Node* next = nullptr;
  if (!node->next || !node->previous) {
    assert(!node->next && !node->previous && "Both or neither should be null.");
    push_back(value);
    next = &m_sentinel;
  } else if (m_storage.size() + 1 < m_storage.capacity()) {
    // Don't have to resize.
    m_storage.push_back(Node{value, nullptr, node});
    // new_node is inserted *before* node
    node->previous->next = &m_storage.back();
    node->previous = &m_storage.back();
    next = node->next;
  } else {
    // We need to resize, so add everything to a new vector, making sure to
    // get the new value before the old node.
    std::vector<Node> vector;
    vector.reserve(m_storage.capacity());

    // Add every value to a new vector, then save the next node so we can
    // return that position.
    Node* current = m_sentinel.next;
    size_type inserted = 0;
    while (current != &m_sentinel) {
      if (current == node) {
        // insert the value before node
        vector.push_back(Node{value, nullptr, nullptr});
        inserted = vector.size() - 1;
      }
      vector.push_back(Node{current->value, nullptr, nullptr});
      current = current->next;
    }
    m_storage = std::move(vector);
    relink();

    if (inserted + 2 < m_storage.size()) {
      next = &m_storage[inserted + 2];
    } else {
      // It's off the end
      next = &m_sentinel;
    }
  }
  return iterator(next);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::erase(
  const_iterator position
)
{
  Node* node = const_cast<Node*>(position.node());
  return erase(node);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::erase(
  Node* node
)
{
  Node* next = nullptr;
  // Remove the node from the vector.
  std::vector<Node> vector;
  vector.reserve(m_storage.capacity());

  // Add every value to a new vector, then save the next node so we can return
  // that position.
  Node* current = m_sentinel.next;
  bool last_node_is_next = false;
  while (current != &m_sentinel) {
    if (current != node) {
      vector.push_back(Node{current->value, nullptr, nullptr});
      if (last_node_is_next) {
        next = &vector.back();
        last_node_is_next = false;
      }
    } else {
      last_node_is_next = true;
    }
    current = current->next;
  }
  m_storage = std::move(vector);
  relink();

  // If the end node is the next node, make next the sentinel.
  if (last_node_is_next) {
    next = &m_sentinel;
  }
  return iterator(next);
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::push_back(const tCONTAINS& value)
{
  if (m_storage.size() + 1 < m_storage.capacity()) {
    // Can add one without resizing
    Node* old_back = empty() ? &m_sentinel : m_sentinel.previous;
    m_storage.push_back(Node{value, old_back, &m_sentinel});
    old_back->next = &m_storage.back();
    m_sentinel.previous = &m_storage.back();
  } else {
    // Need to resize the vector.
    std::vector<Node> vector;
    vector.reserve(m_storage.size() * 2);
    
    for (const tCONTAINS& item : *this) {
      vector.push_back(Node{item, nullptr, nullptr});
    }
    vector.push_back(Node{value, nullptr, nullptr});
    m_storage = std::move(vector);
    relink();
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::push_front(const tCONTAINS& value)
{
  if (m_storage.size() + 1 < m_storage.capacity()) {
    // Can add one without resizing
    Node* old_front = m_sentinel.next;
    m_storage.push_back(Node{value, &m_sentinel, old_front});
    old_front->previous = &m_storage.back();
    m_sentinel.next = &m_storage.back();
  } else {
    // Need to resize the vector.
    std::vector<Node> vector;
    vector.reserve(m_storage.size() * 2);
    
    vector.push_back(Node{value, nullptr, nullptr});
    for (const tCONTAINS& item : *this) {
      vector.push_back(Node{item, nullptr, nullptr});
    }
    m_storage = std::move(vector);
    relink();
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::pop_back()
{
  erase(--end());
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::pop_front()
{
  erase(begin());
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::begin()
{
  return !empty() ? iterator(m_sentinel.next) : end();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::begin() const
{
  return !empty() ? const_iterator(m_sentinel.next) : end();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::end()
{
  return iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::end() const
{
  return const_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::cbegin() const
{
  return !empty() ? const_iterator(m_sentinel.next) : cend();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::cend() const
{
  return const_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::reverse_iterator ArrayList<tCONTAINS>::rbegin()
{
  return !empty() ? reverse_iterator(m_sentinel.previous) : rend();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::reverse_iterator ArrayList<tCONTAINS>::rend()
{
  return reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reverse_iterator ArrayList<tCONTAINS>::rbegin() const
{
  return !empty() ? const_reverse_iterator(m_sentinel.previous) : rend();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reverse_iterator ArrayList<tCONTAINS>::rend() const
{
  return reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reverse_iterator ArrayList<tCONTAINS>::crbegin() const
{
  return !empty() ? const_reverse_iterator(m_sentinel.previous) : crend();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reverse_iterator ArrayList<tCONTAINS>::crend() const
{
  return const_reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tINPUT_ITERATOR>
typename std::enable_if<IsIterator<tINPUT_ITERATOR>::value, void>::type
  ArrayList<tCONTAINS>::assign(tINPUT_ITERATOR first, tINPUT_ITERATOR last)
{
  clear();
  for (tINPUT_ITERATOR it = first; it != last; ++it) {
    m_storage.push_back(Node{*it, nullptr, nullptr});
  }
  relink();
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::assign(size_type size, const value_type& value)
{
  clear();
  m_storage.assign(size, Node{value, nullptr, nullptr});
  relink();
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::swap(ArrayList<tCONTAINS>& list)
{
  // Unimplemented
  std::swap(m_storage, list.m_storage);
  std::swap(m_sentinel, list.m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::relink()
{
  
  if (empty()) {
    m_sentinel.next = nullptr;
    m_sentinel.previous = nullptr;
  } else {
    Node* previous = &m_sentinel;
    for (Node& node : m_storage) {
      node.previous = previous;
      previous->next = &node;

      previous = &node;
    }
    m_sentinel.previous = &m_storage.back();
    m_storage.back().next = &m_sentinel;
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::resize(size_type l_size, value_type value)
{
  // <nnn> inefficient
  size_type current_size = size();
  if (current_size < l_size) {
    for (size_type i = current_size; i < l_size; ++i) {
      push_back(value);
    }
  } else {
    for (size_type i = l_size; i < current_size; ++i) {
      pop_back();
    }
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::splice(
  iterator position,
  ArrayList<tCONTAINS>& list
)
{
  if (list.empty()) return;

  if (size() + list.size() < m_storage.capacity()) {
    // No need to resize
    assert(false && "Not implemented.");
  } else {
    if (empty()) {
      // We're empty, just move the other list into us.
      *this = std::move(list);
    } else {
      Node* node = position.node();
      
      // We need to resize, so add everything to a new vector, making sure to
      // get the new value before the old node.
      std::vector<Node> vector;
      vector.reserve(m_storage.capacity());

      // Add every value to a new vector, then save the next node so we can
      // return that position.
      Node* current = m_sentinel.next;
      while (current != &m_sentinel) {
        if (current == node) {
          // insert the list before node
          for (const tCONTAINS& value : list) {
            vector.push_back(Node{value, nullptr, nullptr});
          }
        }
        vector.push_back(Node{current->value, nullptr, nullptr});
        current = current->next;
      }
      m_storage = std::move(vector);
      relink();
      list.clear();
    }
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::remove(const value_type& value)
{
  remove_if([&value](const value_type& other){return value == other;});
}

//=============================================================================
template <typename tCONTAINS>
template <typename tPREDICATE>
void ArrayList<tCONTAINS>::remove_if(tPREDICATE predicate)
{
  auto it = begin();
  while (it != end()) {
    if (predicate(*it)) {
      it = erase(it.node());
    } else {
      ++it;
    }
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::unique()
{
  // Start with the 2nd element
  auto it = begin();
  value_type last = *it;
  ++it;
  while (it != end()) {
    if (last == *it) {
      it = erase(it);
    } else {
      last = *it;
      ++it;
    }
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::merge(ArrayList<tCONTAINS>& list)
{
  merge(list, std::less<tCONTAINS>());  
}

//=============================================================================
template <typename tCONTAINS>
template <typename tCOMPARATOR>
void ArrayList<tCONTAINS>::merge(ArrayList<tCONTAINS>& list, tCOMPARATOR comparator)
{
  ArrayList<tCONTAINS> merged;
  while (!empty() && !list.empty()) {
    if (comparator(front(), list.front())) {
      merged.push_back(front());
      pop_front();
    } else {
      merged.push_back(list.front());
      list.pop_front();
    }
  }
  // Now at least one of the lists is empty, finish should have elements
  // remaining.
  ArrayList<tCONTAINS>* finish = !empty() ? this : &list;
  while (!finish->empty()) {
    merged.push_back(finish->front());
    finish->pop_front();
  }
  // Now move merged into this
  assign(merged.begin(), merged.end());
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::sort()
{
  sort(std::less<tCONTAINS>());
}

//=============================================================================
template <typename tCONTAINS>
template <typename tCOMPARATOR>
void ArrayList<tCONTAINS>::sort(tCOMPARATOR comparator)
{
  std::sort(
    m_storage.begin(),
    m_storage.end(),
    [&comparator](const Node& a, const Node& b){return comparator(a.value, b.value);}
  );
  relink();
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::reverse()
{
  if (!empty()) {
    Node* current = m_sentinel.next;
    while (current != &m_sentinel) {
      // swap over the stuff
      std::swap(current->next, current->previous);
      current = current->previous;
    }
    // Swap the m_sentinel node
    std::swap(m_sentinel.next, m_sentinel.previous);
  }
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator begin(ArrayList<tCONTAINS>& list)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator begin(const ArrayList<tCONTAINS>& list)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator end(ArrayList<tCONTAINS>& list)
{
  return list.end();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator end(const ArrayList<tCONTAINS>& list)
{
  return list.end();
}

//=============================================================================
template <typename tCONTAINS>
bool operator==(const ArrayList<tCONTAINS>& lhs, const ArrayList<tCONTAINS>& rhs)
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

//=============================================================================
template <typename tCONTAINS>
bool operator!=(const ArrayList<tCONTAINS>& lhs, const ArrayList<tCONTAINS>& rhs)
{
  return !(lhs == rhs);
}

