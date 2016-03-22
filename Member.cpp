#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>

#include "UnitCpp.h"

//=============================================================================
class algorithm {
public:

  template <typename tCONTAINER, typename tCONTAINED>
  static bool member(const tCONTAINER& container, const tCONTAINED& item);
  // Is item a member of container?

private:

  //----- overloaded implementations for generic containers, and specific ones
  template <typename tCONTAINED, typename tCOMPARATOR, typename tALLOCATOR>
  static bool is_member(
    const std::set<tCONTAINED, tCOMPARATOR, tALLOCATOR>& set,
    const tCONTAINED& item
  );
  // Is item a member of the std::set?

  template <
    typename tCONTAINED,
    typename tHASH,
    typename tEQUALS,
    typename tALLOCATOR
  >
  static bool is_member(
    const std::unordered_set<tCONTAINED, tHASH, tEQUALS, tALLOCATOR>& set,
    const tCONTAINED& item
  );
  // Is item a member of the std::unordered_set?

  template <typename tCONTAINER, typename tCONTAINED>
  static bool is_member(const tCONTAINER& container, const tCONTAINED& item);
  // Is item a member of container? This works on any STLish container.
  
};

//=============================================================================
TEST(Member, set)
{
  std::set<int> set = {0, 1, 2, 3, 4};
  TEST_TRUE(algorithm::member(set, 0));
  TEST_TRUE(algorithm::member(set, 1));
  TEST_TRUE(algorithm::member(set, 2));
  TEST_TRUE(algorithm::member(set, 3));
  TEST_TRUE(algorithm::member(set, 4));
  
  TEST_FALSE(algorithm::member(set, -1));
  TEST_FALSE(algorithm::member(set, -2));
  TEST_FALSE(algorithm::member(set, -3));
  TEST_FALSE(algorithm::member(set, -4));
}

//=============================================================================
TEST(Member, unordered_set)
{
  std::unordered_set<double> set = {0, 1, 2, 3, 4};
  TEST_TRUE(algorithm::member(set, 0));
  TEST_TRUE(algorithm::member(set, 1));
  TEST_TRUE(algorithm::member(set, 2));
  TEST_TRUE(algorithm::member(set, 3));
  TEST_TRUE(algorithm::member(set, 4));
  
  TEST_FALSE(algorithm::member(set, -1));
  TEST_FALSE(algorithm::member(set, -2));
  TEST_FALSE(algorithm::member(set, -3));
  TEST_FALSE(algorithm::member(set, -4));
}

//=============================================================================
TEST(Member, vector)
{
  std::vector<int> vector = {0, 1, 2, 3, 4};
  TEST_TRUE(algorithm::member(vector, 0));
  TEST_TRUE(algorithm::member(vector, 1));
  TEST_TRUE(algorithm::member(vector, 2));
  TEST_TRUE(algorithm::member(vector, 3));
  TEST_TRUE(algorithm::member(vector, 4));
  
  TEST_FALSE(algorithm::member(vector, -1));
  TEST_FALSE(algorithm::member(vector, -2));
  TEST_FALSE(algorithm::member(vector, -3));
  TEST_FALSE(algorithm::member(vector, -4));
}

//=============================================================================
TEST(Member, c_array)
{
  int array[5] = {0, 1, 2, 3, 4};
  TEST_TRUE(algorithm::member(array, 0));
  TEST_TRUE(algorithm::member(array, 1));
  TEST_TRUE(algorithm::member(array, 2));
  TEST_TRUE(algorithm::member(array, 3));
  TEST_TRUE(algorithm::member(array, 4));
  
  TEST_FALSE(algorithm::member(array, -1));
  TEST_FALSE(algorithm::member(array, -2));
  TEST_FALSE(algorithm::member(array, -3));
  TEST_FALSE(algorithm::member(array, -4));
}

//=============================================================================
template <typename tCONTAINER, typename tCONTAINED>
bool algorithm::member(const tCONTAINER& container, const tCONTAINED& item)
{
  return is_member(container, item);
}

//=============================================================================
template <typename tCONTAINER, typename tCONTAINED>
bool algorithm::is_member(const tCONTAINER& container, const tCONTAINED& item)
{
  using std::begin;
  using std::end;
  return std::find(begin(container), end(container), item) != end(container);
}

//=============================================================================
template <
  typename tCONTAINED,
  typename tHASH,
  typename tEQUALS,
  typename tALLOCATOR
>
bool algorithm::is_member(
  const std::unordered_set<tCONTAINED, tHASH, tEQUALS, tALLOCATOR>& set,
  const tCONTAINED& item
)
{
  std::cout << "DGC - std::unordered_set" << std::endl;
  return set.find(item) != end(set);
}

//=============================================================================
template <typename tCONTAINED, typename tCOMPARATOR, typename tALLOCATOR>
bool algorithm::is_member(
  const std::set<tCONTAINED, tCOMPARATOR, tALLOCATOR>& set,
  const tCONTAINED& item
)
{
  std::cout << "DGC - std::set" << std::endl;
  return set.find(item) != end(set);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
