//=============================================================================
//
// Based on:
// http://bartoszmilewski.com/2013/11/13/functional-data-structures-in-c-lists/

#include <iostream>
#include <memory>

#include "UnitTest.h"

using namespace std;

//=============================================================================
template <typename T>
struct Item {
  Item(T val, Item const * tail)
    : value(val),
      next(tail)
    {}
  T value;
  Item const * next;
};

//=============================================================================
template<typename T>
class List {
public:

  List()
    : m_head(0)
    {}
  List(T val, List tail)
    : m_head(new Item<T>(val, tail.m_head))
    {}
  
  bool empty() const
    {
      return !m_head;
    }
  T front() const
    {
      assert(!empty());
      return m_head->value;
    }
  
  List pop_front() const
    {
      assert(!empty());
      return List(m_head->next);
    }

private:
  friend class utest_List;
  explicit List(Item<T> const * items)
    : m_head(items)
    {}

  Item<T> const * m_head;
};

//=============================================================================
class utest_List : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_empty();
    test_front();
    test_pop_front();
  }

private:

  void test_empty();
  void test_front();
  void test_pop_front();

};

//=============================================================================
void utest_List::test_empty()
{
  print(DGC_CURRENT_FUNCTION);
  List<int> list_1;
  test(list_1.empty(), "list_1 should be empty");
  List<int> list_2(5, List<int>());
  test(!list_2.empty(), "list_2 should not be empty");
  List<int> list_3(0, list_2);
  test(!list_3.empty(), "list_3 should not be empty");
}

//=============================================================================
void utest_List::test_front()
{
  print(DGC_CURRENT_FUNCTION);
  List<int> list_1(5, List<int>());
  test(list_1.front() == 5, "Front has returned the wrong thing.");
}

//=============================================================================
void utest_List::test_pop_front()
{
  print(DGC_CURRENT_FUNCTION);
  List<int> list_0;
  List<int> list_1(1, list_0);
  List<int> popped = list_1.pop_front();
  test(popped.empty(), "Popped list should be empty.");
  List<int> list_2(2, list_1);
  popped = list_2.pop_front();
  test(popped.front() == 1, "Incorrect value popped.");
}

//=============================================================================
int main() {
  utest_List test;
  test.run_tests();
  return 0;
}
