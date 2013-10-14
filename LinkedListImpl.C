//=============================================================================
//
// 

#include <assert.h>

//=============================================================================
template <typename T>
LinkedList<T>::LinkedList()
  : m_head(0),
    m_size(0)
{
}

//=============================================================================
template <typename T>
const T& LinkedList<T>::operator[](int index) const
{
  assert(0 <= index && index <= size());
  Node* n = m_head;
  for (int i = 0; i < index; ++i) {
    n = n->next;
  }
  return n->data;
}

//=============================================================================
template <typename T>
int LinkedList<T>::size() const
{
  return m_size;
}

//=============================================================================
template <typename T>
LinkedList<T>::~LinkedList()
{
  Node* current = m_head;
  while (current) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

//=============================================================================
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::last_node() const
{
  Node* current = m_head;
  Node* last = 0;
  while (current != 0) {
    last = current;
    current = current->next;
  }
  return last;
}

//=============================================================================
template <typename T>
void LinkedList<T>::prepend(T i)
{
  Node* n = new Node;
  n->data = i;
  n->next = m_head;
  n->prev = 0;
  m_head = n;
  ++m_size;
}

//=============================================================================
template <typename T>
void LinkedList<T>::append(T i)
{
  Node* n = new Node;
  n->data = i;
  n->next = 0;
  Node* last = last_node();
  n->prev = last;
  if (last) {
    assert(last->next == 0);
    last->next = n;
  } else {
    m_head = n;
  }
  ++m_size;
}
