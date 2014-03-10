//=============================================================================
//
// Based on:
// http://bartoszmilewski.com/2013/11/13/functional-data-structures-in-c-lists/

#include <memory>

#include "UnitTest.h"

using namespace std;

//=============================================================================
template<typename T>
class List {
public:

  List()
    : m_head(nullptr)
    {}
  List(T val, List tail)
    : m_head(make_shared<Item<T> >(val, tail.m_head))
    {}

  static List make_repeat(T val, int repeats)
    {
      List list;
      for (int i = 0; i < repeats; ++i) {
        list = List(val, list);
      }
      return list;
    }
  
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

  int size() const
  // O(n) complexity, at least
    {
      return empty() ? 0 : 1 + pop_front().size();
    }

private:
  //===========================================================================
  template <typename U>
  struct Item {
    Item(U val, shared_ptr<Item> tail)
      : value(val),
        next(tail)
      {}
    U value;
    shared_ptr<Item> next;
  };

  explicit List(shared_ptr<Item<T> > items)
    : m_head(items)
    {}

  shared_ptr<Item<T> > m_head;
};

//=============================================================================
template <typename T>
class utest_List : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_empty();
    test_front();
    test_pop_front();
    test_size();
    test_make_repeat();
  }

private:

  void test_empty();
  void test_front();
  void test_pop_front();
  void test_size();
  void test_make_repeat();

};

//=============================================================================
template <typename T>
void utest_List<T>::test_empty()
{
  print(DGC_CURRENT_FUNCTION);
  T list_1;
  test(list_1.empty(), "list_1 should be empty");
  T list_2(5, T());
  test(!list_2.empty(), "list_2 should not be empty");
  T list_3(0, list_2);
  test(!list_3.empty(), "list_3 should not be empty");
}

//=============================================================================
template <typename T>
void utest_List<T>::test_front()
{
  print(DGC_CURRENT_FUNCTION);
  T list_1(5, T());
  test(list_1.front() == 5, "Front has returned the wrong thing.");
}

//=============================================================================
template <typename T>
void utest_List<T>::test_pop_front()
{
  print(DGC_CURRENT_FUNCTION);
  T list_0;
  T list_1(1, list_0);
  T popped = list_1.pop_front();
  test(popped.empty(), "Popped list should be empty.");
  T list_2(2, list_1);
  popped = list_2.pop_front();
  test(popped.front() == 1, "Incorrect value popped.");
}

//=============================================================================
template <typename T>
void utest_List<T>::test_size()
{
  print(DGC_CURRENT_FUNCTION);
  T list_0;
  test(list_0.size() == 0, "Incorrect size for empty list.");
  T list_1(1, list_0);
  test(list_1.size() == 1, "Incorrect size for list size 1.");
  T list_2(2, list_1);
  test(list_2.size() == 2, "Incorrect size for list size 2.");
  T list_3(3, list_2);
  test(list_3.size() == 3, "Incorrect size for list size 3.");
  T list_4(4, list_3);
  test(list_4.size() == 4, "Incorrect size for list size 4.");
}

//=============================================================================
template <typename T>
void utest_List<T>::test_make_repeat()
{
  print(DGC_CURRENT_FUNCTION);
  // put each in it's own scope so that they clear up all the repeat lists
  {
    int size = 10;
    T list = T::make_repeat(-10, size);
    test(list.size() == size, "Wrong size of repeated list.");
    for (int i = 0; i < size; ++i) {
      test(list.front() == -10, "Wrong value in list.");
      list = list.pop_front();
    }
    test(list.empty(), "List should be empty now.");
  }
  {
    T repeated_list = T::make_repeat(5, 100);
    test(repeated_list.size() == 100, "Wrong size of repeated list.");
  }
  {
    T repeated_list = T::make_repeat(5, 1000);
    test(repeated_list.size() == 1000, "Wrong size of repeated list.");
  }
}

//=============================================================================
int main() {
  utest_List<List<int> >().run_tests();
  utest_List<List<double> >().run_tests();
  utest_List<List<float> >().run_tests();
  return 0;
}
