//=============================================================================
//
// Based on:
// http://bartoszmilewski.com/2013/11/13/functional-data-structures-in-c-lists/
#include <assert.h>

#include <memory>

#include <UnitCpp.h>

//=============================================================================
template<typename T>
class List {
public:

  List()
    : m_head(nullptr)
    {}
  List(T val, List tail)
    : m_head(std::make_shared<Item<T> >(val, tail.m_head))
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
    Item(U val, std::shared_ptr<Item> tail)
      : value(val),
        next(tail)
      {}
    U value;
    std::shared_ptr<Item> next;
  };

  explicit List(std::shared_ptr<Item<T> > items)
    : m_head(items)
    {}

  std::shared_ptr<Item<T> > m_head;
};

//=============================================================================
template <typename T>
void test_empty(UnitCpp::TestCase& test_case)
{
  List<T> list_1;
  test_case.test_true(list_1.empty(), "list_1 should be empty");
  List<T> list_2(5, List<T>());
  test_case.test_false(list_2.empty(), "list_2 should not be empty");
  List<T> list_3(0, list_2);
  test_case.test_false(list_3.empty(), "list_3 should not be empty");
}

//=============================================================================
template <typename T>
void test_front(UnitCpp::TestCase& test_case)
{
  List<T> list_1(5, List<T>());
  test_case.test_equal(list_1.front(), 5, "Front has returned the wrong thing.");
}

//=============================================================================
template <typename T>
void test_pop_front(UnitCpp::TestCase& test_case)
{
  List<T> list_0;
  List<T> list_1(1, list_0);
  List<T> popped = list_1.pop_front();
  test_case.test_true(popped.empty(), "Popped list should be empty.");
  List<T> list_2(2, list_1);
  popped = list_2.pop_front();
  test_case.test_equal(popped.front(), 1, "Incorrect value popped.");
}

//=============================================================================
template <typename T>
void test_size(UnitCpp::TestCase& test_case)
{
  List<T> list_0;
  test_case.test_equal(list_0.size(), 0, "Incorrect size for empty list.");
  List<T> list_1(1, list_0);
  test_case.test_equal(list_1.size(), 1, "Incorrect size for list size 1.");
  List<T> list_2(2, list_1);
  test_case.test_equal(list_2.size(), 2, "Incorrect size for list size 2.");
  List<T> list_3(3, list_2);
  test_case.test_equal(list_3.size(), 3, "Incorrect size for list size 3.");
  List<T> list_4(4, list_3);
  test_case.test_equal(list_4.size(), 4, "Incorrect size for list size 4.");
}

//=============================================================================
template <typename T>
void test_make_repeat(UnitCpp::TestCase& test_case)
{
  // put each in it's own scope so that they clear up all the repeat lists
  {
    int size = 10;
    List<T> list = List<T>::make_repeat(-10, size);
    test_case.test_equal(list.size(), size, "Wrong size of repeated list.");
    for (int i = 0; i < size; ++i) {
      test_case.test_equal(list.front(), -10, "Wrong value in list.");
      list = list.pop_front();
    }
    test_case.test_true(list.empty(), "List should be empty now.");
  }
  {
    List<T> repeated_list = List<T>::make_repeat(5, 100);
    test_case.test_equal(repeated_list.size(), 100, "Wrong size of repeated list.");
  }
  {
    List<T> repeated_list = List<T>::make_repeat(5, 1000);
    test_case.test_equal(repeated_list.size(), 1000, "Wrong size of repeated list.");
  }
}

//=============================================================================
template <typename T>
void test_type(UnitCpp::TestCase& test_case)
{
  test_empty<T>(test_case);
  test_front<T>(test_case);
  test_pop_front<T>(test_case);
  test_size<T>(test_case);
  test_make_repeat<T>(test_case);
}

//=============================================================================
TEST(FunctionalList, int)
{
  test_type<int>(*this);
}

//=============================================================================
TEST(FunctionalList, float)
{
  test_type<float>(*this);
}

//=============================================================================
TEST(FunctionalList, double)
{
  test_type<double>(*this);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
