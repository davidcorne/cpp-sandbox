//=============================================================================
//
// 

#include <cassert>

#include <UnitCpp/Test.h>

#define CUSTOM_MEMORY_MAP_CAPACITY 512
#include "MemoryCount.h"

#define UNUSED_VARIABLE
#include "IgnoreDiagnostics.h"

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
TEST(MemoryCount, bounds)
{
  // the number of pointers allocated, not the memory
  size_t pointers_allocated = 0;
  for (size_t i = 0; i < MEMORY_MAP_CAPACITY; ++i) {
    if (!MEMORY_MAP[i].pointer) {
      pointers_allocated = i;
      break;
    }
  }
  for (size_t i = pointers_allocated; i < MEMORY_MAP_CAPACITY; ++i) {
    // I know this is a memory leak, it's probably fine in a test of memory.
    new char('a');
  }
  size_t before = MEMORY_USED;
  char* b = new char('b');
  // once MEMORY_USED has exceeded MEMORY_MAP_CAPACITY it shouldn't increase.
  size_t intermediate = MEMORY_USED;
  delete b;
  size_t after = MEMORY_USED;

  // don't do the TEST stuff till the end, as it allocates memory.
  TEST_EQUAL(before, intermediate);
  TEST_EQUAL(intermediate, after);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
