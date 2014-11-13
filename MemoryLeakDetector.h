//=============================================================================
//
// An RAII class which detects memory leaks. (Needs to be compiled with a debug
// crt e.g. by /MTd - see http://support2.microsoft.com/kb/140584/en)

#ifndef MemoryLeakDetector_H
#define MemoryLeakDetector_H

#include "Compiler.h"
#if COMPILER_TYPE == COMPILER_TYPE_VS

#ifndef _DEBUG
#error "_DEBUG should be defined."
#endif

#include <crtdbg.h>

//=============================================================================
class MemoryLeakDetector {
public:

  class MemoryLeakDetected{};
  
  MemoryLeakDetector();
  
  ~MemoryLeakDetector();

private:

  _CrtMemState m_memstate1;
};

//=============================================================================
MemoryLeakDetector::MemoryLeakDetector()
{
  _CrtMemCheckpoint(&m_memstate1) ; //take the memory snapshot
}

//=============================================================================
MemoryLeakDetector::~MemoryLeakDetector()
{
  _CrtMemState memstate2, memstate3 ; // holds the memory states
  _CrtMemCheckpoint(&memstate2) ; //take the memory snapshot

  int diff = _CrtMemDifference(&memstate3, &m_memstate1, &memstate2);
  if (diff)  {
    _CrtMemDumpAllObjectsSince(&m_memstate1);
    int old_warn_mode= 0;
    _HFILE old_warn_file = 0;
    int old_error_mode = 0;
    _HFILE old_error_file = 0;
    int old_assert_mode = 0;
    _HFILE old_assert_file= 0;
    old_warn_mode = _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    old_warn_file = _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    old_error_mode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    old_error_file = _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    old_assert_mode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    old_assert_file = _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtMemDumpAllObjectsSince(&m_memstate1);
    _CrtSetReportMode(_CRT_WARN, old_warn_mode);
    _CrtSetReportFile(_CRT_WARN, old_warn_file);
    _CrtSetReportMode(_CRT_ERROR, old_error_mode);
    _CrtSetReportFile(_CRT_ERROR, old_error_file);
    _CrtSetReportMode(_CRT_ASSERT, old_assert_mode);
    _CrtSetReportFile(_CRT_ASSERT, old_assert_file);
  }
  if (diff) {
    // there were memory leaks.
    throw MemoryLeakDetected();
  }
}


#else
#error "No <crtdbg> outside of COMPILER_TYPE_VS"
#endif
#endif
