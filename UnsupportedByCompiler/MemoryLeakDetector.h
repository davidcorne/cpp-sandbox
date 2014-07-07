//=============================================================================
//
// An RAII class which detects memory leaks.

#ifndef MemoryLeakDetector_H
#define MemoryLeakDetector_H

#include <crtdbg.h>

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
}

//=============================================================================
MemoryLeakDetector::~MemoryLeakDetector()
{
  
  throw MemoryLeakDetected();
}

#endif
