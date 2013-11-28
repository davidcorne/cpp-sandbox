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
  // take the memory snapshot  
  _CrtMemCheckpoint(&m_memory);
  // holds the memory states  
  _CrtMemState memstate2, memstate3; 
  _CrtMemCheckpoint(&memstate2) ; //take the memory snapshot

  bool diff = _CrtMemDifference(&memstate3, &m_memory, &memstate2);
  if (diff)  {
    _CrtMemDumpAllObjectsSince(&m_memstate1);
  }
  throw MemoryLeakDetected();
}

//=============================================================================
void fail_test()
{
  assert(false);
}

//=============================================================================
class utest_MemoryLeakDetector : UnitTest {
public:

  void run_tests() {
    set_terminate(fail_test);
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
  print(__FUNCTION__);
  bool exception = true;
  try {
    MemoryLeakDetector leak_detector;
    int* i = new int;
    delete i;
  } catch (MemoryLeakDetector::MemoryLeakDetected execption) {
    exception = false;
  }
  test(!exception, "Detected a memory leak");
}

//=============================================================================
void utest_MemoryLeakDetector::test_memory_leak()
{
  print(__FUNCTION__);
  bool exception = false;
  try {
    MemoryLeakDetector leak_detector;
    int* i = new int;
  } catch (MemoryLeakDetector::MemoryLeakDetected execption) {
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
