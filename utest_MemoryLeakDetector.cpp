//=============================================================================
//
// 

#include <cassert>

#include <iostream>

#include <UnitCpp.h>

#define UNUSED_VARIABLE
#include "IgnoreDiagnostics.h"

#include "MemoryLeakDetector.h"

bool LEAKED = false;

void test_memory_leak_handler()
{
  assert(!LEAKED && "Should have been reset since last leak");
  LEAKED = true;
}

//=============================================================================
TEST(MemoryLeakDetector, memory_leak)
{
  LEAKED = false;
  {
    MemoryLeakDetector detector(test_memory_leak_handler);
    {
      int* i = new int(0);
    }
  }
  TEST_TRUE(LEAKED, "Memory has leaked.");
}

//=============================================================================
TEST(MemoryLeakDetector, leaked_array)
{
  LEAKED = false;
  {
    MemoryLeakDetector detector(test_memory_leak_handler);
    {
      size_t size = 10;
      int* array = new int[size];
    }
  }
  TEST_TRUE(LEAKED, "Memory has leaked.");
}

//=============================================================================
TEST(MemoryLeakDetector, no_leak)
{
  MemoryLeakDetector detector;
  {
    int* i = new int(0);
    delete i;
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

