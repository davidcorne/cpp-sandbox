//=============================================================================
//
// 

#include <cassert>

#include <UnitCpp.h>

#include "MemoryCount.h"

//=============================================================================
TEST(MemoryCount, count)
{
  size_t memory_start = MEMORY_USED;
  int* i = new int;
  size_t memory_allocated = MEMORY_USED - memory_start;
  delete i;
  size_t memory_end = MEMORY_USED;
  TEST_EQUAL(memory_allocated, sizeof(int));
  TEST_EQUAL(memory_start, memory_end);
}

//=============================================================================
TEST(MemoryCount, array)
{
  assert(MEMORY_USED < MEMORY_MAP_CAPACITY && "Out of capacity.");
  size_t memory_start = MEMORY_USED;
  int* array = new int[15];
  size_t memory_allocated = MEMORY_USED - memory_start;
  delete[] array;
  size_t memory_end = MEMORY_USED;
  TEST_EQUAL(memory_allocated, 15 * sizeof(int));
  TEST_EQUAL(memory_start, memory_end);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
