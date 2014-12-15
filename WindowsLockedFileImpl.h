//=============================================================================
// An implementation of a locked file for windows.

#ifndef WindowsLockedFileImpl_H
#define WindowsLockedFileImpl_H

#include "LockedFileImpl.h"

#include <algorithm>

struct FileHandle;

//=============================================================================
class WindowsLockedFileImpl : public LockedFileImpl {
public:

  WindowsLockedFileImpl(Path file, ErrorPtr& error);
  // Locks file.

  virtual std::string read() const override;
  
  virtual void write(std::string contents) override;
  
  virtual ~WindowsLockedFileImpl();
  // Unlocks the file

private:
  void reset_file_pointer() const;
  // Resets the file pointer to the beginning of the file
  // Note: treat the location of the file pointer as mutable.
  
  std::unique_ptr<FileHandle> m_file_handle;
};

//----- Source
#if DGC_WINDOWS_DEV 
#include <Windows.h>

#include "LockFileError.h"
#include "GenericError.h"

//=============================================================================
struct FileHandle
{
  HANDLE handle;
};

//=============================================================================
WindowsLockedFileImpl::WindowsLockedFileImpl(Path path, ErrorPtr& error)
  : m_file_handle(new FileHandle)
{
  m_file_handle->handle = CreateFile(
    path.path().c_str(),          // LPCTSTR lpFileName,
    GENERIC_READ | GENERIC_WRITE, // DWORD dwDesiredAccess,
    FILE_SHARE_READ,              // DWORD dwShareMode,
    NULL,                         // LPSECURITY_ATTRIBUTES lpSecurityAttribs,
    OPEN_EXISTING,                // DWORD dwCreationDisposition,
    FILE_ATTRIBUTE_NORMAL,        // DWORD dwFlagsAndAttributes,
    NULL                          // HANDLE hTemplateFile
  );
  if (m_file_handle->handle == INVALID_HANDLE_VALUE) {
    DWORD error_code = GetLastError();
    if (error_code == ERROR_SHARING_VIOLATION) {
      error = ErrorPtr(new LockFileError(path));
    } else {
      PVOID lpMsgBuf;
      FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |           
        FORMAT_MESSAGE_FROM_SYSTEM |               
        FORMAT_MESSAGE_IGNORE_INSERTS,             // DWORD dwFlags,      
        NULL,                                      // LPCVOID lpSource,   
        error_code,                                // DWORD dwMessageId,  
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // DWORD dwLanguageId, 
        (LPTSTR) &lpMsgBuf,                        // LPTSTR lpBuffer,    
        0,                                         // DWORD nSize,        
        NULL                                       // va_list *Arguments  
      );
      char* msg = static_cast<char*>(lpMsgBuf);
      std::string error_message(msg);
      error = ErrorPtr(new GenericError(error_message));
    }
  } else {
    // find the file size
    LARGE_INTEGER file_size;
    BOOL ok = FALSE;
    ok = GetFileSizeEx(
      m_file_handle->handle,        // HANDLE hFile,            
      &file_size                    // PLARGE_INTEGER lpFileSize
    );
    assert(ok);

    OVERLAPPED sOverlapped;
    // lock the file

    ok = LockFileEx(
      m_file_handle->handle,     // HANDLE hFile,
      LOCKFILE_EXCLUSIVE_LOCK |
      LOCKFILE_FAIL_IMMEDIATELY, // DWORD dwFlags,
      0,                         // DWORD dwReserved,
      file_size.LowPart,         // DWORD nNumberOfBytesToLockLow,
      file_size.HighPart,        // DWORD nNumberOfBytesToLockHigh,
      &sOverlapped               // LPOVERLAPPED lpOverlapped
    );
    assert(ok);
  }
}

//=============================================================================
void WindowsLockedFileImpl::write(std::string contents)
{
  reset_file_pointer();
  LARGE_INTEGER file_size;
  BOOL ok = FALSE;
  ok = GetFileSizeEx(
    m_file_handle->handle,        // HANDLE hFile,            
    &file_size                    // PLARGE_INTEGER lpFileSize
  );
  assert(ok);
  // If the file is longer you want to overwrite it all.
  DWORD to_write = std::max<DWORD>(
    file_size.LowPart,
    static_cast<DWORD>(contents.size())
  );
  DWORD bytes_written;
  WriteFile(
    m_file_handle->handle, // HANDLE hFile,
    contents.c_str(),      // LPCVOID lpBuffer,
    to_write,              // DWORD nNumberOfBytesToWrite,
    &bytes_written,        // LPDWORD lpNumberOfBytesWritten,
    NULL                   // LPOVERLAPPED lpOverlapped
  );
  
}

//=============================================================================
std::string WindowsLockedFileImpl::read() const
{
  reset_file_pointer();
  BOOL ok = FALSE;
  LARGE_INTEGER file_size;
  ok = GetFileSizeEx(
    m_file_handle->handle, // HANDLE hFile,
    &file_size             // PLARGE_INTEGER lpFileSize
  );
  assert(ok);

  char* buffer = new char[file_size.LowPart + 1];
  DWORD  bytes_read = 0;
  ReadFile(
    m_file_handle->handle, // HANDLE hFile,
    buffer,                // LPVOID lpBuffer,
    file_size.LowPart,     // DWORD nNumberOfBytesToRead,
    &bytes_read,           // LPDWORD lpNumberOfBytesRead,
    NULL                   // LPOVERLAPPED lpOverlapped
  );
  // null terminate the string
  buffer[bytes_read] = '\0';
  std::string contents(buffer);
  delete[] buffer;
  return contents;
}

//=============================================================================
WindowsLockedFileImpl::~WindowsLockedFileImpl()
{
  CloseHandle(m_file_handle->handle);
}

//=============================================================================
void WindowsLockedFileImpl::reset_file_pointer() const
{
  SetFilePointer(
    m_file_handle->handle, // HANDLE hFile,
    0,                     // LONG lDistanceToMove,
    NULL,                  // PLONG lpDistanceToMoveHigh,
    FILE_BEGIN             // DWORD dwMoveMethod
  );
}

#endif // DGC_WINDOWS_DEV
#endif
