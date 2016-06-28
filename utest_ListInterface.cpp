//=============================================================================
// Tests for std::list type interfaces.

#define UNUSED_VARIABLE 1
#define UNREACHABLE_CODE 1
#include "IgnoreDiagnostics.h"

// Test double including
#include "ArrayList.h"
#include "ArrayList.h"

#include "List.h"
#include "List.h"

#include <list>

#include <UnitCpp.h>

//=============================================================================
template <typename tLIST>
class ListUtest {
public:

  ListUtest(UnitCpp::TestCase& test_case);

  void run_tests();
  
private:

  using value_type = typename tLIST::value_type;

  void test_members();

  void test_ctor();

  void test_copying();

  void test_iterate_empty();
  
  void test_capacity();

  void test_accessors();

  void test_modifiers();

  void test_assign();

  void test_swap();

  void test_resize();
  
  void test_push_back();

  void test_push_front();

  void test_internal_removals();

  void test_internal_insert();

  void test_reverse_iteration();

  void test_splice();
  
  void test_remove();
  
  void test_remove_if();
  
  void test_unique();
  
  void test_merge();
  
  void test_sort();
  
  void test_reverse();

  bool is_array_list() const;
  
  ListUtest(const ListUtest&) = delete;
  ListUtest operator=(const ListUtest&) = delete;
  
  UnitCpp::TestCase& m_test;
};

//=============================================================================
template <typename tLIST>
ListUtest<tLIST>::ListUtest(UnitCpp::TestCase& test_case)
  : m_test(test_case)
{
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::run_tests()
{
  test_members();
  test_ctor();
  test_copying();
  test_iterate_empty();
  test_reverse_iteration();
  test_capacity();
  test_accessors();
  test_push_back();
  test_push_front();
  test_modifiers();
  test_assign();
  test_swap();
  test_resize();
  test_internal_removals();
  test_internal_insert();
  test_splice();
  test_remove();
  test_remove_if();
  test_unique();
  test_merge();
  test_sort();
  test_reverse();
}

//=============================================================================
template <typename T>
struct exists{};

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_members()
{
  // Test that these typedefs exist on the list type.
  exists<typename tLIST::value_type>();
  exists<typename tLIST::allocator_type>();
  exists<typename tLIST::size_type>();
  exists<typename tLIST::difference_type>();
  exists<typename tLIST::reference>();
  exists<typename tLIST::const_reference>();
  exists<typename tLIST::pointer>();
  exists<typename tLIST::const_pointer>();
  exists<typename tLIST::iterator>();
  exists<typename tLIST::const_iterator>();
  exists<typename tLIST::reverse_iterator>();
  exists<typename tLIST::const_reverse_iterator>();
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_ctor()
{
  tLIST list;
  tLIST other(list);
  list = other;
  tLIST third{0, 1, 2, 3, 4, 5};
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_copying()
{
  tLIST a{0, 1, 2, 3};
  tLIST b(a);
  m_test.test_equal(
    a,
    b,
    "Copy constructor should work."
  );
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_iterate_empty()
{
  tLIST list;
  for (auto i : list) {

  }
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_reverse_iteration()
{
  if (is_array_list()) return;

  tLIST list = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<value_type> results;
  for (auto it = list.rbegin(); it != list.rend(); ++it) {
    results.push_back(*it);
  }
  std::vector<value_type> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m_test.test_equal(
    expected,
    results,
    "Should iterate in reverse order."
  );
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_capacity()
{
  tLIST list{0, 1, 2, 3, 4, 5};
  m_test.test_equal(list.size(), 6u, "Size should be 6.");
  m_test.test_false(list.empty(), "List should not be empty.");
  m_test.test_true(
    tLIST().empty(),
    "A default constructed list should be empty."
  );

  // Don't actually test max_size() but make sure it's callable
  std::size_t size = list.max_size();
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_accessors()
{
  tLIST list = {0, 1, 2, 3, 4, 5};
  m_test.test_equal(list.front(), 0, "0 should be first element.");
  m_test.test_equal(list.back(), 5, "5 should be last element.");

  list.front() = -10;
  list.back() = 0;
  m_test.test_equal(list.front(), -10, "New first element should be -10.");
  m_test.test_equal(list.back(), 0, "New last element should be 0.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_modifiers()
{
  tLIST list = {0, 1};
  list.clear();
  m_test.test_true(list.empty(), "Clearing list should empty it.");

  list.insert(list.end(), 5);
  m_test.test_false(list.empty(), "insert: list should be {5}");
  m_test.test_equal(list.front(), 5, "insert: list should be {5}");
  m_test.test_equal(list.back(), 5, "insert: list should be {5}");

  list.push_back(6);
  m_test.test_equal(list.front(), 5, "push_back: list should be {5, 6}");
  m_test.test_equal(list.back(), 6, "push_back: list should be {5, 6}");
  
  list.push_front(4);
  m_test.test_equal(list.front(), 4, "push_front: list should be {4, 5, 6}");
  m_test.test_equal(list.back(), 6, "push_front: list should be {4, 5, 6}");

  if (is_array_list()) return;

  list.pop_front();
  m_test.test_equal(list.front(), 5, "pop_front: list should be {5, 6}");
  m_test.test_equal(list.back(), 6, "pop_front: list should be {5, 6}");

  list.pop_back();
  m_test.test_equal(list.front(), 5, "pop_back: list should be {5}");
  m_test.test_equal(list.back(), 5, "pop_back: list should be {5}");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_assign()
{
  if (is_array_list()) return;

  tLIST expected;
  tLIST list;
  
  std::vector<value_type> vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  list.assign(begin(vector), end(vector));
  m_test.test_equal(vector.size(), list.size(), "Assign should keep size.");

  expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m_test.test_equal(
    list,
    expected,
    "Should have assigned the correct content."
  );

  list.assign(5, 0);
  expected = {0, 0, 0, 0, 0};
  m_test.test_equal(
    list,
    expected,
    "Should have assigned the correct content."
  );
  
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_swap()
{
  if (is_array_list()) return;

  tLIST a = {0, 1, 2, 3, 4};
  tLIST b;

  tLIST original_a(a);
  tLIST original_b(b);

  a.swap(b);
  m_test.test_equal(a, original_b, "a should have swapped with b.");
  m_test.test_equal(b, original_a, "b should have swapped with a.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_resize()
{
  if (is_array_list()) return;

  // Larger.
  tLIST list;
  list.resize(5u);
  m_test.test_equal(list.size(), 5u, "list should resize to 5 elements.");

  // Reduce.
  list.resize(0u);
  m_test.test_true(list.empty(), "resize(0) should clear the list.");

  // Larger, but with an element.
  list.resize(2u, 3);
  m_test.test_equal(list.size(), 2u, "list should resize to 2 elements.");
  m_test.test_equal(list.front(), 3, "list should fill with 3s");
  m_test.test_equal(list.back(), 3, "list should fill with 3s");
  
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_internal_removals()
{
  if (is_array_list()) return;

  tLIST list = {0, 1, 2, 3, 4, 5};
  // Remove each even element
  auto it = begin(list);
  while (it != end(list)) {
    bool even = (static_cast<int>(*it) % 2) == 0;
    if (even) {
      it = list.erase(it);
    } else {
      ++it;
    }
  }
  m_test.test_equal(list.size(), 3u, "Should have removed 3 elements.");
  tLIST expected = {1, 3, 5};
  m_test.test_equal(list, expected, "Should have removed even elements.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_internal_insert()
{
  if (is_array_list()) return;

  tLIST list = {0, 1, 2};
  for (auto it = begin(list); it != end(list); ++it) {
    list.insert(it, (*it) * 2);
  }
  tLIST expected = {0, 0, 2, 1, 4, 2};
  m_test.test_equal(
    list,
    expected,
    "Should insert 2x in front of each x in list."
  );
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_push_back()
{
  tLIST list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  tLIST result;
  for (auto i : list) {
    result.push_back(i);
  }
  m_test.test_equal(
    list,
    result,
     "push_back() should be the same as initializer_list."
  );
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_push_front()
{
  tLIST list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<value_type> fill = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  tLIST result;
  for (auto i : fill) {
    result.push_front(i);
  }
  m_test.test_equal(
    list,
    result,
    "push_front() should be the same as initializer_list."
  );
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_splice()
{
  if (is_array_list()) return;

  tLIST to = {0, 4, 5, 6};
  tLIST from = {1, 2, 3};
  auto position = begin(to);
  ++position;
  assert(*position == 4 && "position should be pointing at 4");

  // Add the elements from from into to before position.
  to.splice(position, from);

  tLIST result = {0, 1, 2, 3, 4, 5, 6};
  m_test.test_equal(to, result, "The splice didn't work.");
  m_test.test_true(from.empty(), "Splice should empty the from list.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_remove()
{
  if (is_array_list()) return;

  tLIST expected;
  tLIST list = {0, 0, 0, 0, 1, 2, 3, 4};
  
  list.remove(5);
  expected = {0, 0, 0, 0, 1, 2, 3, 4};
  m_test.test_equal(list, expected, "Should have removed nothing.");

  list.remove(0);
  expected = {1, 2, 3, 4};
  m_test.test_equal(list, expected, "Should have removed 0.");

  list.remove(2);
  expected = {1, 3, 4};
  m_test.test_equal(list, expected, "Should have removed 2.");

  list.remove(4);
  expected = {1, 3};
  m_test.test_equal(list, expected, "Should have removed 2.");

  list.remove(1);
  expected = {3};
  m_test.test_equal(list, expected, "Should have removed 2.");

  list.remove(3);
  expected = {};
  m_test.test_equal(list, expected, "Should have removed 2.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_remove_if()
{
  if (is_array_list()) return;

  tLIST expected;
  tLIST list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Remove numbers divisible by 3
  list.remove_if([](value_type i)->bool{return static_cast<int>(i) % 3 == 0;});
  expected = {1, 2, 4, 5, 7, 8};
  m_test.test_equal(
    list,
    expected,
    "Should have removed anything divisible by 3"
  );

  // Remove nothing
  list.remove_if([](value_type i)->bool{return i > 9;});
  expected = {1, 2, 4, 5, 7, 8};
  m_test.test_equal(list, expected, "Shouldn't have removed anything.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_unique()
{
  if (is_array_list()) return;

  tLIST list = {0, 0, 1, 2, 1, 1, 3};
  list.unique();
  tLIST expected = {0, 1, 2, 1, 3};
  m_test.test_equal(list, expected, "Should remove the repeated elements.");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_merge()
{
  if (is_array_list()) return;

  tLIST a = {0, 2, 4, 6, 8};
  tLIST b = {1, 3, 5, 7, 9};
  tLIST expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.merge(b);
  m_test.test_equal(a, expected, "Should have merged b into a.");
  m_test.test_true(b.empty(), "The merge should have emptied b.");
  
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_sort()
{
  if (is_array_list()) return;

  {
    tLIST expected = {0, 1};
    tLIST list = {1, 0};
    list.sort();
    m_test.test_equal(
      list,
      expected,
      "Should be able to sort a 2 element list."
    );
  }
  {
    tLIST expected = {0, 1, 2};
    tLIST list = {2, 0, 1};
    list.sort();
    m_test.test_equal(
      list,
      expected,
      "Should be able to sort a 3 element list."
    );
  }
  {
    tLIST expected;
    tLIST list = {9, 8, 7, 6, 5, 3, 4, 2, 1, 0};
  
    list.sort();
    expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (value_type v : list) {
      std::cout << v << ", ";
    }
    std::cout << "\n";
    m_test.test_equal(list, expected, "list should have been sorted.");

    // Now reverse it.
    list.sort([](value_type a, value_type b){return b < a;});
    expected = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    m_test.test_equal(list, expected, "Should have reversed the list.");
  }
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_reverse()
{
  if (is_array_list()) return;

  tLIST list = {1, 3, 5, 7, 2, 4, 6};
  list.reverse();
  
  tLIST expected = {6, 4, 2, 7, 5, 3, 1};
  m_test.test_equal(list, expected, "Should have reversed it.");

  expected = {1, 3, 5, 7, 2, 4, 6};
  list.reverse();
  m_test.test_equal(list, expected, "Should have reversed it.");

  list.reverse();
  list.reverse();
  m_test.test_equal(list, expected, "Double reverse, should keep the same.");
}

//=============================================================================
template <typename tLIST>
bool ListUtest<tLIST>::is_array_list() const
{
  return
    std::is_same<tLIST, ArrayList<int>>::value ||
    std::is_same<tLIST, ArrayList<double>>::value ||
    std::is_same<tLIST, ArrayList<float>>::value;
}

//=============================================================================
TEST(std_list, int)
{
  ListUtest<std::list<int>>(*this).run_tests();
}

//=============================================================================
TEST(std_list, double)
{
  ListUtest<std::list<double>>(*this).run_tests();
}

//=============================================================================
TEST(std_list, float)
{
  ListUtest<std::list<float>>(*this).run_tests();
}

//=============================================================================
TEST(ArrayList, int)
{
  ListUtest<ArrayList<int>>(*this).run_tests();
}

//=============================================================================
TEST(ArrayList, double)
{
  ListUtest<ArrayList<double>>(*this).run_tests();
}

//=============================================================================
TEST(ArrayList, float)
{
  ListUtest<ArrayList<float>>(*this).run_tests();
}

//=============================================================================
TEST(List, int)
{
  ListUtest<List<int>>(*this).run_tests();
}

//=============================================================================
TEST(List, double)
{
  ListUtest<List<double>>(*this).run_tests();
}

//=============================================================================
TEST(List, float)
{
  ListUtest<List<float>>(*this).run_tests();
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
