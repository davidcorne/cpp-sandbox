//=============================================================================
//
// 

#include <crtdbg.h>

#include "../UnitTest.h"

using namespace std;

//=============================================================================
class MemoryLeakDetector {
public:
  class MemoryLeakDetected{};
  
  MemoryLeakDetector();
  ~MemoryLeakDetector();

private:

  _CrtMemState m_memory;
};

//=============================================================================
MemoryLeakDetector::MemoryLeakDetector()
{
  // take the memory snapshot  
  _CrtMemCheckpoint(&m_memory); 
}

//=============================================================================
MemoryLeakDetector::~MemoryLeakDetector()
{
  // holds the memory states  
  _CrtMemState memstate2, memstate3; 
  _CrtMemCheckpoint(&memstate2) ; //take the memory snapshot

  bool diff = _CrtMemDifference(&memstate3, &m_memory, &memstate2);
  if (diff)  {
    _CrtMemDumpAllObjectsSince(&m_memory);
    throw MemoryLeakDetected();
  }
}

//=============================================================================
class utest_MemoryLeakDetector : UnitTest {
public:

  void run_tests() {
    test_no_memory_leak();
    test_memory_leak();
  }
private:
  void test_no_memory_leak();
  void test_memory_leak();
};


//=============================================================================
void utest_MemoryLeakDetector::test_no_memory_leak()
{
  print(DGC_CURRENT_FUNCTION);
  bool exception = false;
  try {
    {
      MemoryLeakDetector leak_detector;
      int* i = new int;
      delete i;
    }
  } catch (...) {
    exception = true;
  }
  test(!exception, "Detected a memory leak");
}

//=============================================================================
void utest_MemoryLeakDetector::test_memory_leak()
{
  print(DGC_CURRENT_FUNCTION);
  bool exception = false;
  try {
    MemoryLeakDetector leak_detector;
    char* leak = new char[5];
  } catch (...) {
    exception = true;
  }
  test(exception, "Did not detect a memory leak");
}

//=============================================================================
int main() {
  utest_MemoryLeakDetector utest;
  utest.run_tests();
  return 0;
}
