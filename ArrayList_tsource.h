//----- Node source

//=============================================================================
template <typename tCONTAINS>
bool ArrayList<tCONTAINS>::Node::operator==(
  const typename ArrayList<tCONTAINS>::Node& other
) const
{
  return this == &other;
}

//----- ArrayList

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList() = default;

//=============================================================================
template <typename tCONTAINS>
ArrayList<tCONTAINS>::ArrayList(std::initializer_list<tCONTAINS> init)
{
  m_storage.reserve(init.size());
  for (const tCONTAINS& contains: init) {
    push_back(contains);
  }
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
  return m_storage[front_node_index()].value;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reference ArrayList<tCONTAINS>::front() const
{
  return m_storage[front_node_index()].value;
}
 
//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::reference ArrayList<tCONTAINS>::back()
{
  return m_storage[back_node_index()].value;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_reference ArrayList<tCONTAINS>::back() const
{
  return m_storage[back_node_index()].value;
}
 
//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::clear()
{
  m_storage.clear();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::insert(
  const_iterator position,
  const tCONTAINS& value
)
{
  if (position != end()) {
    auto it = find(position);
    Node* position_node = &(*it);
    Node node{value, position_node->previous, position_node};
    m_storage.push_back(node);
  } else {
    push_back(value);
  }
  
  return iterator(&m_storage.back());
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::erase(
  const_iterator position
)
{
  // Note: position must be valid and dereferenceable i.e. can't be end().
  auto it = find(position);
  // Link the before and after nodes together.
  Node& removing = *it;
  Node* before = removing.previous;
  Node* after = removing.next;
  if (before) {
    before->next = after;
  }
  if (after) {
    after->previous = before;
  }
  // Now do the actual removing
  it = m_storage.erase(it);

  // Return an iterator
  iterator ret_it;
  if (it != m_storage.end()) {
    ret_it = iterator(&(*it));
  }
  return ret_it;
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::push_back(const tCONTAINS& value)
{
  // Can't cache the old node, as the vector may resize and then it'll be
  // invalid.
  size_type index = back_node_index();
  Node node{value, index != max_size() ? &m_storage[index] : nullptr, nullptr};
  m_storage.push_back(node);
  if (index != max_size()) {
    m_storage[index].next = &m_storage.back();
  }
}

//=============================================================================
template <typename tCONTAINS>
void ArrayList<tCONTAINS>::push_front(const tCONTAINS& value)
{
  // Can't cache the old node, as the vector may resize and then it'll be
  // invalid.
  size_type index = front_node_index();
  Node node{value, nullptr, index != max_size() ? &m_storage[index] : nullptr};
  m_storage.push_back(node);
  if (index != max_size()) {
    m_storage[index].previous = &m_storage.front();
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
  size_type index = front_node_index();
  return NodeIterator(
    index != max_size() ? &m_storage[index] : nullptr
  );
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::begin() const
{
  size_type index = front_node_index();
  return NodeIteratorConst(
    index != max_size() ? &m_storage[index] : nullptr
  );
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator ArrayList<tCONTAINS>::end()
{
  return NodeIterator();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::end() const
{
  return NodeIteratorConst();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::cbegin() const
{
  size_type index = front_node_index();
  return NodeIteratorConst(
    index != max_size() ? &m_storage[index] : nullptr
  );
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator ArrayList<tCONTAINS>::cend() const
{
  return NodeIteratorConst();
}

//=============================================================================
template <typename tCONTAINS>
typename std::vector<typename ArrayList<tCONTAINS>::Node>::iterator ArrayList<tCONTAINS>::find(
  const_iterator position
)
{
  auto it = m_storage.end();
  if (position != end()) {
    it = std::find(m_storage.begin(), m_storage.end(), *position.node());
  }
  return it;
}

//=============================================================================
template <typename tCONTAINS>
typename std::vector<typename ArrayList<tCONTAINS>::Node>::const_iterator ArrayList<tCONTAINS>::find(
  const_iterator position
) const
{
  return const_cast<ArrayList<tCONTAINS>*>(this)->find(position);
}


//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::size_type ArrayList<tCONTAINS>::front_node_index() const
{
  size_type index = max_size();
  for (size_type i = 0; i < m_storage.size(); ++i) {
    if (!m_storage[i].previous) {
      assert(index == max_size() && "Should be only one front node");
      index = i;
    }
  }
  return index;
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::size_type ArrayList<tCONTAINS>::back_node_index() const
{
  size_type index = max_size();
  for (size_type i = 0; i < m_storage.size(); ++i) {
    if (!m_storage[i].next) {
      assert(index == max_size() && "Should be only one back node");
      index = i;
    }
  }
  return index;
}

