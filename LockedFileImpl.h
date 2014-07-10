//=============================================================================
// Abstract implementation of a locked file.

#ifndef LockedFileImpl_H
#define LockedFileImpl_H

#include "Error.h"

//=============================================================================
class LockedFileImpl {
public:

  LockedFileImpl();

  virtual std::string read() const = 0;

  virtual void write(std::string contents) = 0;
  
  virtual ~LockedFileImpl() = 0;
};

//=============================================================================
std::unique_ptr<LockedFileImpl> lock_file(Path path, ErrorPtr& error);

//----- Source

#include "WindowsLockedFileImpl.h"
#include "LinuxLockedFileImpl.h"
#include "DGC_OS.h"

LockedFileImpl::LockedFileImpl() = default;
LockedFileImpl::~LockedFileImpl() = default;

//=============================================================================
std::unique_ptr<LockedFileImpl> lock_file(Path path, ErrorPtr& error)
{
  std::unique_ptr<LockedFileImpl> ptr(
#ifdef DGC_WINDOWS_DEV    
    new WindowsLockedFileImpl(path, error)
#else
    new LinuxLockedFileImpl(path, error)
#endif
  );
  if (error) {
    ptr = nullptr;
  }
  return ptr;
}

#endif
