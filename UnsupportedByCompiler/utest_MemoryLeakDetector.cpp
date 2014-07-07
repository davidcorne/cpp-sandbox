//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"
#include "MemoryLeakDetector.h"

using namespace std;

//=============================================================================
class utest_MemoryLeakDetector : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_memory_leak();
    test_no_memory_leak();
  }

private:

  void test_memory_leak();

  void test_no_memory_leak();

};

//=============================================================================
void utest_MemoryLeakDetector::test_memory_leak()
{
  print(DGC_CURRENT_FUNCTION);
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
  test(exception_thrown, "An exception should have been thrown.");
    
}

//=============================================================================
void utest_MemoryLeakDetector::test_no_memory_leak()
{
  print(DGC_CURRENT_FUNCTION);
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
  test(!exception_thrown, "An exception should not have been thrown.");
    
}

//=============================================================================
int main() {
  utest_MemoryLeakDetector test;
  test.run_tests();
  return 0;
}
