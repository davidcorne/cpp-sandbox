//=============================================================================
//
// An RAII class which detects memory leaks. 

#ifndef MemoryLeakDetector_H
#define MemoryLeakDetector_H

#include "MemoryCount.h"

typedef void (*MemoryLeakHandler)();

//=============================================================================
class MemoryLeakDetector {
public:

  MemoryLeakDetector();
  // Uses the default_handler
  
  ~MemoryLeakDetector();

private:

  UNITCPP_FRIEND_TEST(MemoryLeakDetector, memory_leak);
  static void default_handler();
  
  MemoryLeakDetector(MemoryLeakHandler handler);
  
  MemoryLeakHandler m_handler;
  std::size_t m_initial_memory;
};

//=============================================================================
void MemoryLeakDetector::default_handler()
{
  assert(false && "Memory leak detected.");
}

//=============================================================================
MemoryLeakDetector::MemoryLeakDetector()
  : m_handler(&MemoryLeakDetector::default_handler),
    m_initial_memory(0)
{
  m_initial_memory = MEMORY_USED;
}

//=============================================================================
MemoryLeakDetector::MemoryLeakDetector(MemoryLeakHandler handler)
  : m_handler(handler),
    m_initial_memory(0)
{
  m_initial_memory = MEMORY_USED;
}

//=============================================================================
MemoryLeakDetector::~MemoryLeakDetector()
{
  bool diff = m_initial_memory != MEMORY_USED;
  if (diff) {
    m_handler();
  }
}
#endif
