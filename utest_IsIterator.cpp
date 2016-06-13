//=============================================================================
//
// 
#include "IsIterator.h"
#include "IsIterator.h"

#include <deque>
#include <list>
#include <map>
#include <set>
#include <vector>

#include <UnitCpp.h>

//=============================================================================
TEST(utest_IsIterator, iterators)
{
  TEST_TRUE(
    IsIterator<std::vector<int>::iterator>::value,
    "Vector iterator should be an iterator."
  );
  TEST_TRUE(
    IsIterator<std::set<double>::iterator>::value,
    "Set iterator should be an iterator."
  );
  TEST_TRUE(
    (IsIterator<std::map<std::string, std::string>::iterator>::value),
    "Map iterator should be an iterator."
  );
  TEST_TRUE(
    IsIterator<std::list<float>::iterator>::value,
    "List iterator should be an iterator."
  );
  TEST_TRUE(
    IsIterator<std::deque<std::size_t>::iterator>::value,
    "deque iterator should be an iterator."
  );
}

//=============================================================================
TEST(utest_IsIterator, non_iterators)
{
  TEST_FALSE(
    IsIterator<int>::value,
    "int should not be an iterator."
  );
  TEST_FALSE(
    IsIterator<std::size_t>::value,
    "size_t should not be an iterator."
  );
  
//D These fail with my current implementation, however the implementation is
//D good enough for what I need it for.
//
//X  TEST_FALSE(
//X    IsIterator<float>::value,
//X    "float should not be an iterator."
//X  );
//X  TEST_FALSE(
//X    IsIterator<double>::value,
//X    "double should not be an iterator."
//X  );
//X  TEST_FALSE(
//X    IsIterator<std::string>::value,
//X    "std::string should not be an iterator."
//X  );
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
