//=============================================================================
// Unfortunately this won't work. This is because linux only honours locks ifndef
// they are looking for it. For instance remove() does not check flock, so it
// will remove a seemingly locked file :(


#ifndef LinuxLockedFileImpl_H
#define LinuxLockedFileImpl_H

#include "LockedFileImpl.h"

struct FileHandle;

//=============================================================================
class LinuxLockedFileImpl : public LockedFileImpl {
public:

  LinuxLockedFileImpl(Path path, ErrorPtr& error);

  virtual std::string read() const override;

  virtual void write(std::string contents) override;
  
  virtual ~LinuxLockedFileImpl();
    
private:
  std::unique_ptr<FileHandle> m_file_handle;
};

//----- Source

#ifdef DGC_WINDOWS_DEV 

#include "LockFileError.h"
#include <sys/file.h>

#include "Printer.h"

//=============================================================================
struct FileHandle
{
  FILE* handle;
};

//=============================================================================
LinuxLockedFileImpl::LinuxLockedFileImpl(Path path, ErrorPtr& error)
  : m_file_handle(new FileHandle)
{
  
  m_file_handle->handle = fopen(path.path().c_str(), "r+");
  int file_descriptor = fileno(m_file_handle->handle);
  int result = flock(file_descriptor, LOCK_EX | LOCK_NB);
  print("result ", result);
  if (result != 0) {
    error = ErrorPtr(new LockFileError(path));
  }
}

std::string LinuxLockedFileImpl::read() const
{
  return "";
}

void LinuxLockedFileImpl::write(std::string contents)
{
    
}

//=============================================================================
LinuxLockedFileImpl::~LinuxLockedFileImpl()
{
    
}

#endif // DGC_WINDOWS_DEV

#endif
