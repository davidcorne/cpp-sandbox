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
  assign(init.begin(), init.end());
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>::List(const List<tCONTAINS>& list)
  : List()
{
  assign(list.begin(), list.end());
}

//=============================================================================
template <typename tCONTAINS>
List<tCONTAINS>& List<tCONTAINS>::operator=(const List<tCONTAINS>& list)
{
  assign(list.begin(), list.end());
  return *this;
}

// <nnn> //=============================================================================
// <nnn> template <typename tCONTAINS>
// <nnn> List<tCONTAINS>::List(const List<tCONTAINS>&& list)
// <nnn> {
  
// <nnn> }

// <nnn> //=============================================================================
// <nnn> template <typename tCONTAINS>
// <nnn> List<tCONTAINS>& List<tCONTAINS>::operator=(const List<tCONTAINS>&& list)
// <nnn> {
  
// <nnn> }

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
  m_sentinel.next = nullptr;
  m_sentinel.previous = nullptr;
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::insert(
  const_iterator position,
  const tCONTAINS& value
)
{
  Node* node = const_cast<Node*>(position.node());
  if (!node->next || !node->previous) {
    // If either are null, we should be inserting at end()
    assert(node == &m_sentinel && "We should be inserting at end()");
    push_back(value);
  } else {
    Node* new_node = new Node{value, nullptr, node};
    // new_node is inserted *before* node
    node->previous->next = new_node;
    node->previous = new_node;
  }
  return iterator(node->next);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::erase(
  const_iterator position
)
{
  Node* node = const_cast<Node*>(position.node());
  return erase(node);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::erase(
  Node* node
)
{
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
  Node* back = empty() ? &m_sentinel : m_sentinel.previous;
  back->next = node;
  m_sentinel.previous = node;
  node->next = &m_sentinel;
  node->previous = back;
  assert(node->previous && node->next && "Next or previous shouldn't be null.");
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::push_front(const tCONTAINS& value)
{
  Node* node = new Node{value, nullptr, nullptr};
  Node* front = empty() ? &m_sentinel : m_sentinel.next;
  m_sentinel.next = node;
  front->previous = node;
  node->next = front;
  node->previous = &m_sentinel;
  assert(node->previous && node->next && "Next or previous shouldn't be null.");
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
  return !empty() ? iterator(m_sentinel.next) : end();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::begin() const
{
  return !empty() ? const_iterator(m_sentinel.next) : end();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator List<tCONTAINS>::end()
{
  return iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::end() const
{
  return const_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::cbegin() const
{
  return !empty() ? const_iterator(m_sentinel.next) : cend();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator List<tCONTAINS>::cend() const
{
  return const_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::reverse_iterator List<tCONTAINS>::rbegin()
{
  return !empty() ? reverse_iterator(m_sentinel.previous) : rend();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::reverse_iterator List<tCONTAINS>::rend()
{
  return reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reverse_iterator List<tCONTAINS>::rbegin() const
{
  return !empty() ? const_reverse_iterator(m_sentinel.previous) : rend();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reverse_iterator List<tCONTAINS>::rend() const
{
  return reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reverse_iterator List<tCONTAINS>::crbegin() const
{
  return !empty() ? const_reverse_iterator(m_sentinel.previous) : crend();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_reverse_iterator List<tCONTAINS>::crend() const
{
  return const_reverse_iterator(&m_sentinel);
}

//=============================================================================
template <typename tCONTAINS>
template <typename tINPUT_ITERATOR>
typename std::enable_if<IsIterator<tINPUT_ITERATOR>::value, void>::type
  List<tCONTAINS>::assign(tINPUT_ITERATOR first, tINPUT_ITERATOR last)
{
  clear();
  Node* current = &m_sentinel;
  for (auto it = first; it != last; ++it) {
    value_type value = *it;
    Node* new_node = new Node{value, current, nullptr};
    current->next = new_node;
    current = new_node;
  }
  m_sentinel.previous = current;
  current->next = &m_sentinel;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::assign(size_type size, const value_type& value)
{
  clear();
  Node* current = &m_sentinel;
  for (size_type i = 0; i < size; ++i) {
    Node* new_node = new Node{value, current, nullptr};
    current->next = new_node;
    current = new_node;
  }
  m_sentinel.previous = current;
  current->next = &m_sentinel;
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::swap(List<tCONTAINS>& list)
{
  Node* my_previous = m_sentinel.previous;
  Node* my_next = m_sentinel.next;
  Node* list_previous = list.m_sentinel.previous;
  Node* list_next = list.m_sentinel.next;
  std::swap(m_sentinel, list.m_sentinel);
  if (my_previous || my_next) {
    assert(my_previous && my_next && "If you have one, you should have both.");
    my_previous->next = &list.m_sentinel;
    my_next->previous = &list.m_sentinel;
  }
  if (list_previous || list_next) {
    assert(list_previous && list_next && "If you have one, you should have both.");
    list_previous->next = &m_sentinel;
    list_next->previous = &m_sentinel;
  }
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::resize(size_type l_size, value_type value)
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
void List<tCONTAINS>::splice(iterator position, List<tCONTAINS>& list)
{
  if (!list.empty()) {
    Node* current = position.node();
    Node* first = current->previous;
  
    Node* sequence_start = list.m_sentinel.next;
    first->next = sequence_start;
    sequence_start->previous = first;

    Node* sequence_end = list.m_sentinel.previous;
    current->previous = sequence_end;
    sequence_end->next = current;

    list.m_sentinel.next = nullptr;
    list.m_sentinel.previous = nullptr;
  }
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::remove(const value_type& value)
{
  remove_if([&value](const value_type& other){return value == other;});
}

//=============================================================================
template <typename tCONTAINS>
template <typename tPREDICATE>
void List<tCONTAINS>::remove_if(tPREDICATE predicate)
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
void List<tCONTAINS>::unique()
{
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::merge(List<tCONTAINS>& list)
{
  merge(list, std::less<tCONTAINS>());  
}

//=============================================================================
template <typename tCONTAINS>
template <typename tCOMPARATOR>
void List<tCONTAINS>::merge(List<tCONTAINS>& list, tCOMPARATOR comparator)
{
  List<tCONTAINS> merged;
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
  List<tCONTAINS>* finish = !empty() ? this : &list;
  while (!finish->empty()) {
    merged.push_back(finish->front());
    finish->pop_front();
  }
  // Now move merged into this
  assign(merged.begin(), merged.end());
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::sort()
{
  sort(std::less<tCONTAINS>());
}

//=============================================================================
template <typename tCONTAINS>
template <typename tCOMPARATOR>
void List<tCONTAINS>::sort(tCOMPARATOR comparator)
{
  (void)comparator;
  if (!empty()) {

  }
}

//=============================================================================
template <typename tCONTAINS>
void List<tCONTAINS>::reverse()
{

}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator begin(List<tCONTAINS>& list)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator begin(const List<tCONTAINS>& list)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator end(List<tCONTAINS>& list)
{
  return list.end();
}

//=============================================================================
template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator end(const List<tCONTAINS>& list)
{
  return list.end();
}

//=============================================================================
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

//=============================================================================
template <typename tCONTAINS>
bool operator!=(const List<tCONTAINS>& lhs, const List<tCONTAINS>& rhs)
{
  return !(lhs == rhs);
}

