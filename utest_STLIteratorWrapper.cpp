//=============================================================================
//
// 

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS
#include <iostream>
#include <vector>

#include <UnitCpp.h>

#include "STLIteratorWrapper.h"


//=============================================================================
TEST(STLIteratorWrapper, vector_iteration)
{
  std::vector<int> container = {0, 1, 2, 3, 4, 5};
  STLIteratorWrapper<std::vector<int>::iterator> iter(
    std::begin(container),
    std::end(container)
  );
  TEST_EQUAL(iter.m_iter, end(container), "Should start on an invalid iterator.");
  TEST_TRUE(++iter, "++ should give true.");
  TEST_EQUAL(iter.m_iter, begin(container), "Should be at the beginning.");

  TEST_EQUAL(iter(), 0, "Wrong element");
  TEST_TRUE(++iter, "++ should give true.");

  TEST_EQUAL(iter(), 1, "Wrong element");
  TEST_TRUE(++iter, "++ should give true.");

  TEST_EQUAL(iter(), 2, "Wrong element");
  TEST_TRUE(++iter, "++ should give true.");

  TEST_EQUAL(iter(), 3, "Wrong element");
  TEST_TRUE(++iter, "++ should give true.");

  TEST_EQUAL(iter(), 4, "Wrong element");
  TEST_TRUE(++iter, "++ should give true.");

  TEST_EQUAL(iter(), 5, "Wrong element");
  TEST_FALSE(++iter, "++ should give false.");
}

//=============================================================================
TEST(STLIteratorWrapper, empty)
{
  std::vector<int> container;
  STLIteratorWrapper<std::vector<int>::iterator> iter(
    std::begin(container),
    std::end(container)
  );
  TEST_FALSE(++iter, "Should start false.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif
