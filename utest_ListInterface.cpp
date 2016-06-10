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

  void test_members();

  void test_ctor();

  void test_capacity();

  void test_accessors();

  void test_modifiers();

  void test_internal_removals();

  void test_internal_insert();

  void test_push_back();

  void test_push_front();

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
  test_capacity();
  test_accessors();
  test_push_back();
  test_push_front();
  test_modifiers();
  test_internal_removals();
  test_internal_insert();
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

  list.pop_front();
  m_test.test_equal(list.front(), 5, "pop_front: list should be {5, 6}");
  m_test.test_equal(list.back(), 6, "pop_front: list should be {5, 6}");

  list.pop_back();
  m_test.test_equal(list.front(), 5, "pop_back: list should be {5}");
  m_test.test_equal(list.back(), 5, "pop_back: list should be {5}");
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_internal_removals()
{
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
  m_test.test_equal(list.size(), 3u);
  tLIST expected = {1, 3, 5};
  m_test.test_equal(list, expected);
}

//=============================================================================
template <typename tLIST>
void ListUtest<tLIST>::test_internal_insert()
{
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
  std::vector<typename tLIST::value_type> fill = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
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
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<ArrayList<int>>(*this).run_tests();
}

//=============================================================================
TEST(ArrayList, double)
{
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<ArrayList<double>>(*this).run_tests();
}

//=============================================================================
TEST(ArrayList, float)
{
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<ArrayList<float>>(*this).run_tests();
}

//=============================================================================
TEST(List, int)
{
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<List<int>>(*this).run_tests();
}

//=============================================================================
TEST(List, double)
{
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<List<double>>(*this).run_tests();
}

//=============================================================================
TEST(List, float)
{
  // Make sure it compiles, but don't run it.
  return;
  ListUtest<List<float>>(*this).run_tests();
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
