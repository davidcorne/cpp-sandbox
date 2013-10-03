//=============================================================================
//
// 

#include <iostream>
#include "UnitTest.h"

using namespace std;

//=============================================================================
class LinkedList {
public:

  LinkedList();

  ~LinkedList();

  void append(int i);
  
private:

  //===========================================================================
  struct Node {
    int data;
    Node* next;
    Node* prev;
  };
  
  Node* last_node() const;
  
  LinkedList& operator=(const LinkedList&);
  LinkedList(LinkedList&);
  // Can't be copied
  
  friend class utest_LinkedList;
  
  Node* m_head;
};

//=============================================================================
LinkedList::LinkedList()
  : m_head(0)
{
}

//=============================================================================
LinkedList::~LinkedList()
{
  Node* current = m_head;
  while (current) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

//=============================================================================
LinkedList::Node* LinkedList::last_node() const
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
void LinkedList::append(int i)
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
}

//=============================================================================
class utest_LinkedList : public UnitTest {
public:
  void test_last_node();
  void test_append();
  void test_prev();
  
  void run_tests() {
    test_append();
    test_last_node();
    test_prev();
  }
};

//=============================================================================
void utest_LinkedList::test_append()
{
  LinkedList l;
  l.append(1);
  test(l.m_head->data == 1, "Append has not appended 1.");
  l.append(2);
  test(l.m_head->data == 1, "Second append has not modified m_head.");
  LinkedList::Node* second = l.m_head->next;
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
  LinkedList l;
  l.append(0);
  LinkedList::Node* n_0 = l.last_node();
  l.append(1);
  LinkedList::Node* n_1 = l.last_node();
  l.append(2);
  LinkedList::Node* n_2 = l.last_node();
  test(n_0->prev == 0, "First node non 0 previous.");
  test(n_1->prev == n_0, "1st node prev is not 0th node.");
  test(n_2->prev == n_1, "2nd node prev is not 1st node.");
}

//=============================================================================
void utest_LinkedList::test_last_node()
{
  LinkedList l;
  LinkedList::Node* last = l.last_node();
  test(last == 0, "Last should be null.");
  l.append(0);
  last = l.last_node();
  test(last != 0, "Last should not be null.");
}

//=============================================================================
int main() {
  utest_LinkedList t;
  t.run_tests();
  return 0;
}
