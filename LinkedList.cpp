//=============================================================================
//
// 

#include <iostream>
#include "UnitTest.h"

using namespace std;

//=============================================================================
template <typename T>
class LinkedList {
public:

  LinkedList();

  ~LinkedList();

  void append(T i);

  void prepend(T i);

  int length() const;

  const T& operator[](int i) const;

  bool operator==(const LinkedList& other) const;
  bool operator!=(const LinkedList& other) const;
  
private:

  //===========================================================================
  struct Node {
    T data;
    Node* next;
    Node* prev;
  };
  
  Node* last_node() const;
  
  LinkedList& operator=(const LinkedList&);
  LinkedList(LinkedList&);
  // Can't be copied
  
  friend class utest_LinkedList;
  
  Node* m_head;
  int m_length;
};

//=============================================================================
template <typename T>
LinkedList<T>::LinkedList()
  : m_head(0),
    m_length(0)
{
}

//=============================================================================
template <typename T>
const T& LinkedList<T>::operator[](int index) const
{
  assert(0 <= index && index <= length());
  Node* n = m_head;
  for (int i = 0; i < index; ++i) {
    n = n->next;
  }
  return n->data;
}

//=============================================================================
template <typename T>
bool LinkedList<T>::operator==(const LinkedList& other) const
{
  bool equal = length() == other.length();
  if (equal) {
    for (int i = 0; i < length(); ++i) {
      equal = this->operator[](i) == other[i];
      if (!equal) {
        break;
      }
    }
  }
  return equal;
}

//=============================================================================
template <typename T>
bool LinkedList<T>::operator!=(const LinkedList& other) const
{
  return !(this->operator==(other));
}

//=============================================================================
template <typename T>
int LinkedList<T>::length() const
{
  return m_length;
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
  ++m_length;
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
  ++m_length;
}

//=============================================================================
class utest_LinkedList : public UnitTest {
public:
  void test_last_node();
  void test_append();
  void test_length();
  void test_prepend();
  void test_prev();
  void test_string_list();
  void test_random_access();
  void test_equal();
  void test_not_equal();
  
  void run_tests() {
    test_append();
    test_length();
    test_prepend();
    test_last_node();
    test_prev();
    test_string_list();
    test_random_access();
    test_equal();
    test_not_equal();
  }
};

//=============================================================================
void utest_LinkedList::test_random_access()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> list;
  list.append(0);
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  test(list[0] == 0, "operator[] returns incorrectly.");
  test(list[1] == 1, "operator[] returns incorrectly.");
  test(list[2] == 2, "operator[] returns incorrectly.");
  test(list[3] == 3, "operator[] returns incorrectly.");
  test(list[4] == 4, "operator[] returns incorrectly.");
}

//=============================================================================
void utest_LinkedList::test_length()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<char> list;
  test(list.length() == 0, "Empty list should have length 0.");
  list.append('a');
  test(list.length() == 1, "List should have length 1.");
  list.append('b');
  test(list.length() == 2, "List should have length 2.");
  list.append('c');
  test(list.length() == 3, "List should have length 3.");
}

//=============================================================================
void utest_LinkedList::test_string_list()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<string> string_list;
  string_list.append("hello");
  string_list.append("world");
  test(string_list.m_head->data == "hello", "hello not written to head.");
  test(string_list.last_node()->data == "world", "world not written to tail.");
}

//=============================================================================
void utest_LinkedList::test_prepend()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  assert(l.m_head->data == 1);
  l.prepend(-1);
  test(l.m_head->data == -1, "Prepend failed.");
}

//=============================================================================
void utest_LinkedList::test_append()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> l;
  l.append(1);
  test(l.m_head->data == 1, "Append has not appended 1.");
  l.append(2);
  test(l.m_head->data == 1, "Second append has not modified m_head.");
  LinkedList<int>::Node* second = l.m_head->next;
  test(second->data == 2, "Second append has not appended 2.");
  l.append(3);
  test(l.last_node()->data == 3, "Append failed for 3rd append.");
  l.append(4);
  test(l.last_node()->data == 4, "Append failed for 4th append.");
  l.append(5);
  test(l.last_node()->data == 5, "Append failed for 5th append.");
  l.append(6);
  test(l.last_node()->data == 6, "Append failed for 6th append.");
  l.append(7);
  test(l.last_node()->data == 7, "Append failed for 7th append.");
  l.append(8);
  test(l.last_node()->data == 8, "Append failed for 8th append.");
  l.append(9);
  test(l.last_node()->data == 9, "Append failed for 9th append.");
}

//=============================================================================
void utest_LinkedList::test_prev()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> l;
  l.append(0);
  LinkedList<int>::Node* n_0 = l.last_node();
  l.append(1);
  LinkedList<int>::Node* n_1 = l.last_node();
  l.append(2);
  LinkedList<int>::Node* n_2 = l.last_node();
  test(n_0->prev == 0, "First node non 0 previous.");
  test(n_1->prev == n_0, "1st node prev is not 0th node.");
  test(n_2->prev == n_1, "2nd node prev is not 1st node.");
}

//=============================================================================
void utest_LinkedList::test_last_node()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> l;
  LinkedList<int>::Node* last = l.last_node();
  test(last == 0, "Last should be null.");
  l.append(0);
  last = l.last_node();
  test(last != 0, "Last should not be null.");
}

//=============================================================================
void utest_LinkedList::test_equal()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<int> first;
  LinkedList<int> second;
  int limit = 50;
  for (int i = 0; i < limit; ++i) {
    first.append(i);
  }
  test(!(first == second), "operator== returns incorrectly.");
  for (int i = 0; i < limit; ++i) {
    second.append(i);
  }
  test(first == second, "operator== returns incorrectly.");
  LinkedList<int> third;
  for (int i = 0; i < limit; ++i) {
    third.prepend(i);
  }
  test(
    !(first == third),
    "Same length but different content should be different"
  );
}

//=============================================================================
void utest_LinkedList::test_not_equal()
{
  print(DGC_CURRENT_FUNCTION);
  LinkedList<char> first;
  LinkedList<char> second;
  test(!(first != second), "Empty lists should not be unequal");
  first.append('a');
  test(first != second, "Different length lists should be unequal.");
  second.append('b');
  test(first != second, "Same length, different content should be unequal.");
}

//=============================================================================
int main() {
  utest_LinkedList t;
  t.run_tests();
  return 0;
}
