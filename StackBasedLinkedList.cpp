//=============================================================================
//
// 

#include "ObserverPointer.h"

#include <UnitCpp.h>

struct LinkedListOutOfSpaceException : std::exception
{
};

//=============================================================================
template <typename T, unsigned I=50>
class LinkedList {
public:

  // Join item to the begining of the list.
  void prepend(T item);

  // Pop the first item from the list.
  T pop();

    
private:

  UNITCPP_FRIEND_TEST(StackBasedLinkedList, prepend);
  
  template <typename U>
  friend class LinkedListIterator;
  
  template <typename U>
  friend class LinkedListConstIterator;
  
  struct Node {
    Node()
      : data(),
        next(nullptr),
        previous(nullptr),
        invalid(true)
      {}
    
    T data;
    ObserverPtr<Node> next;
    ObserverPtr<Node> previous;
    bool invalid;
  };

  ObserverPtr<Node> m_head;

  struct NodeStore {
    Node store[I];
    
    ObserverPtr<Node> next();
  };

  static NodeStore s_node_store;
};

//=============================================================================
template <typename T>
class LinkedListConstIterator {
public:

  // Default constructor, (acts as end iterator)
  LinkedListConstIterator();

  // Constructor, (acts as begin iterator)
  LinkedListConstIterator(const LinkedList<T>& list);

  // Dereference operator.
  const T& operator*() const;

  // Pointer calling operator.
  const T* operator->() const;

  // Increment the iterator.
  void operator++();

  // Equality operator.
  bool operator==(const LinkedListConstIterator<T>& other) const;

  // Inequality operator.
  bool operator!=(const LinkedListConstIterator<T>& other) const;

private:

  ObserverPtr<const typename LinkedList<T>::Node> m_current;
};

// Return a begin iterator
template <typename T>
LinkedListConstIterator<T> cbegin(LinkedList<T>& list);
  
// Return an end iterator
template <typename T>
LinkedListConstIterator<T> cend(LinkedList<T>& list);

//=============================================================================
template <typename T>
class LinkedListIterator {
public:

  // Default constructor, (acts as end iterator)
  LinkedListIterator();

  // Constructor, (acts as begin iterator)
  LinkedListIterator(LinkedList<T>& list);

  // Dereference operator.
  T& operator*() const;

  // Pointer calling operator.
  T* operator->() const;

  // Increment the iterator.
  void operator++();

  // Equality operator.
  bool operator==(const LinkedListIterator<T>& other) const;

  // Inequality operator.
  bool operator!=(const LinkedListIterator<T>& other) const;

private:

  ObserverPtr<typename LinkedList<T>::Node> m_current;
};

// Return a begin iterator
template <typename T>
LinkedListIterator<T> begin(LinkedList<T>& list);
  
// Return an end iterator
template <typename T>
LinkedListIterator<T> end(LinkedList<T>& list);

//=============================================================================
TEST(StackBasedLinkedList, constructor)
{

  LinkedList<int> int_list;
  LinkedList<double> double_list;
  LinkedList<std::string> string_list;

  LinkedList<const int> const_int_list;
}

//=============================================================================
TEST(StackBasedLinkedList, prepend)
{
  LinkedList<double> list;
  TEST_FALSE(list.m_head);
  
  list.prepend(5.5);
  TEST_TRUE(list.m_head);
  TEST_EQUAL(list.m_head->data, 5.5);
  TEST_FALSE(list.m_head->next);
  TEST_FALSE(list.m_head->previous);
  TEST_FALSE(list.m_head->invalid);
  auto previous = list.m_head;
  
  list.prepend(4.4);
  TEST_TRUE(list.m_head);
  TEST_EQUAL(list.m_head->data, 4.4);
  TEST_TRUE(list.m_head->next);
  TEST_EQUAL(list.m_head->next, previous);
  TEST_FALSE(list.m_head->previous);
  TEST_FALSE(list.m_head->invalid);
}

//=============================================================================
TEST(StackBasedLinkedList, iterator)
{
  LinkedList<int> int_list;
  int_list.prepend(1);
  for (auto it = cbegin(int_list); it != cend(int_list); ++it) {
    TEST_EQUAL(*it, 1);
  }
  for (int i: int_list) {
    TEST_EQUAL(i, 1);
  }

  int_list.prepend(2);
  int_list.prepend(3);
  int_list.prepend(4);
  int_list.prepend(5);
  int_list.prepend(6);
  int_list.prepend(7);
  int_list.prepend(8);
  int_list.prepend(9);
  int_list.prepend(10);
  std::vector<int> equivilant;
  for (int i: int_list) {
    equivilant.push_back(i);
  }
  TEST_EQUAL(equivilant.size(), 10);
  TEST_EQUAL(equivilant[0], 10);
  TEST_EQUAL(equivilant[1], 9);
  TEST_EQUAL(equivilant[2], 8);
  TEST_EQUAL(equivilant[3], 7);
  TEST_EQUAL(equivilant[4], 6);
  TEST_EQUAL(equivilant[5], 5);
  TEST_EQUAL(equivilant[6], 4);
  TEST_EQUAL(equivilant[7], 3);
  TEST_EQUAL(equivilant[8], 2);
  TEST_EQUAL(equivilant[9], 1);
}

//=============================================================================
TEST(StackBasedLinkedList, limit)
{
  LinkedList<int, 3> list;
  list.prepend(0);
  list.prepend(1);
  list.prepend(2);
  bool throws = false;
  try {
    list.prepend(3);
  } catch (LinkedListOutOfSpaceException e) {
    throws = true;
  }
  TEST_TRUE(throws);
}

//----- Source
//----- LinkedList

template <typename T, unsigned I>
typename LinkedList<T, I>::NodeStore LinkedList<T, I>::s_node_store;

//=============================================================================
template <typename T, unsigned I>
void LinkedList<T, I>::prepend(T item)
{
  ObserverPtr<Node> free = s_node_store.next();
  free->data = item;
  free->next = m_head;
  free->invalid = false;
  m_head = free;
}

//=============================================================================
template <typename T, unsigned I>
ObserverPtr<typename LinkedList<T, I>::Node> LinkedList<T, I>::NodeStore::next()
{
  ObserverPtr<Node> node;
  for (Node& n : store) {
    if (n.invalid) {
      node = ObserverPtr<Node>(&n);
      break;
    }
  }
  if (!node) {
    throw LinkedListOutOfSpaceException();
  }
  return node;
}

//----- LinkedListIterator

//=============================================================================
template <typename T>
LinkedListIterator<T>::LinkedListIterator()
  : m_current(nullptr)
{
}

//=============================================================================
template <typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedList<T>& list)
  : m_current(list.m_head)
{
}

//=============================================================================
// Dereference operator.
template <typename T>
T& LinkedListIterator<T>::operator*() const
{
  return m_current->data;
}

//=============================================================================
// Pointer calling operator.
template <typename T>
T* LinkedListIterator<T>::operator->() const
{
  return &(m_current->data);
}

//=============================================================================
// Increment the iterator.
template <typename T>
void LinkedListIterator<T>::operator++()
{
  m_current = m_current->next;
}
  
//=============================================================================
// Equality operator.
template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& other) const
{
  return m_current == other.m_current;
}

//=============================================================================
// Inequality operator.
template <typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& other) const
{
  return !(*this == other);
}

//=============================================================================
// Return a begin iterator
template <typename T>
LinkedListIterator<T> begin(LinkedList<T>& list)
{
  return LinkedListIterator<T>(list);
}
 
//=============================================================================
// Return an end iterator
template <typename T>
LinkedListIterator<T> end(LinkedList<T>& list)
{
  return LinkedListIterator<T>();
}

//----- LinkedListConstIterator

//=============================================================================
template <typename T>
LinkedListConstIterator<T>::LinkedListConstIterator()
  : m_current(nullptr)
{
}

//=============================================================================
template <typename T>
LinkedListConstIterator<T>::LinkedListConstIterator(const LinkedList<T>& list)
  : m_current(list.m_head)
{
}

//=============================================================================
// Dereference operator.
template <typename T>
const T& LinkedListConstIterator<T>::operator*() const
{
  return m_current->data;
}

//=============================================================================
// Pointer calling operator.
template <typename T>
const T* LinkedListConstIterator<T>::operator->() const
{
  return &(m_current->data);
}

//=============================================================================
// Increment the iterator.
template <typename T>
void LinkedListConstIterator<T>::operator++()
{
  m_current = m_current->next;
}
  
//=============================================================================
// Equality operator.
template <typename T>
bool LinkedListConstIterator<T>::operator==(const LinkedListConstIterator<T>& other) const
{
  return m_current == other.m_current;
}

//=============================================================================
// Inequality operator.
template <typename T>
bool LinkedListConstIterator<T>::operator!=(const LinkedListConstIterator<T>& other) const
{
  return !(*this == other);
}

//=============================================================================
// Return a begin iterator
template <typename T>
LinkedListConstIterator<T> cbegin(LinkedList<T>& list)
{
  return LinkedListConstIterator<T>(list);
}
 
//=============================================================================
// Return an end iterator
template <typename T>
LinkedListConstIterator<T> cend(LinkedList<T>& list)
{
  return LinkedListConstIterator<T>();
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
