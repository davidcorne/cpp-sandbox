//=============================================================================
//
// 

#include "Compiler.h"
#if COMPILER_TYPE == COMPILER_TYPE_VS
#define UNUSED_VARIABLE
#include "IgnoreDiagnostics.h"

#include <iostream>

#include <UnitCpp/Test.h>

#include "MemoryLeakDetector.h"

//=============================================================================
TEST(MemoryLeakDetector, memory_leak)
{
  bool exception_thrown = false;
  try {
    {
      MemoryLeakDetector detector;
      {
        int* i = new int(0);
      }
    }
  } catch (...) {
    exception_thrown = true;
  }
  TEST_TRUE(exception_thrown, "An exception should have been thrown.");
}

//=============================================================================
TEST(MemoryLeakDetector, no_memory_leak)
{
  bool exception_thrown = false;
  try {
    {
      MemoryLeakDetector detector;
      {
        int* i = new int(0);
        delete i;
      }
    }
  } catch (...) {
    exception_thrown = true;
  }
  TEST_FALSE(exception_thrown, "An exception should not have been thrown.");
    
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN(COMPILER_TYPE_VS)
#endif
