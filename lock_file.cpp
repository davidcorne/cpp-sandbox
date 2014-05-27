//=============================================================================
//
//D An RAII file locker. On creation, this will lock the file given.
//

#ifdef __CYGWIN__

#include "UnitTest.h"
#include "Path.h"

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <memory>

// types: classes, enums, typedefs, namespaces

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class Error {
public:

  Error();
  
  virtual std::string to_string() const = 0;

  virtual ~Error() = 0;
};

//=============================================================================
class LockFileError : public Error {
public:
  
  LockFileError(Path path);

  virtual std::string to_string() const;

  virtual ~LockFileError();
  
private:
  Path m_path;
};

//=============================================================================
class GenericError : public Error {
public:
  GenericError(std::string error);

  virtual std::string to_string() const;

  virtual ~GenericError();
  
private:
  std::string m_error;
};

struct FileHandle;

//=============================================================================
class LockedFile {
public:

  LockedFile(Path file, std::shared_ptr<Error>& error);
  // Locks file.

  std::string read() const;
  
  void write(std::string contents);
  
  ~LockedFile();
  // Unlocks the file

private:
  void reset_file_pointer() const;
  // Resets the file pointer to the beginning of the file
  // Note: treat the location of the file pointer as mutable.
  
  std::unique_ptr<FileHandle> m_file_handle;
};


//=============================================================================
class utest_lock_file : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_lock();
    test_multiple_lock();
    test_read();
    test_write();
    test_multiple_read();
    test_overwrite();
  }

private:

  void test_lock();
  void test_multiple_lock();
  void test_read();
  void test_write();
  void test_multiple_read();
  void test_overwrite();
  void write_file(Path path, std::string contents)
    {
      std::ofstream file_stream(path.path());
      file_stream << contents;
      file_stream.close();
    }

};

//=============================================================================
void utest_lock_file::test_write()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    std::shared_ptr<Error> error;
    LockedFile lock_file(path, error);
    assert(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    std::string whole_file = lock_file.read();
    test(whole_file == new_contents, "Write incorrect.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_overwrite()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    std::shared_ptr<Error> error;
    LockedFile lock_file(path, error);
    assert(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    assert(lock_file.read() == new_contents);
    lock_file.write("");
    test(lock_file.read() == std::string(""), "Overwriting file fails.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_multiple_read()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    std::shared_ptr<Error> error;
    LockedFile locked_file(path, error); 
    assert(!error);
    std::string first_read(locked_file.read());
    assert(first_read == contents);
    std::string second_read(locked_file.read());
    test(first_read == second_read, "Read inconsistent.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_read()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    std::shared_ptr<Error> error;
    LockedFile lock_file(path, error);
    assert(!error);
    test(lock_file.read() == contents, "Contents is wrong.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_lock()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    std::shared_ptr<Error> error;
    LockedFile lock(path, error);
    assert(!error);
    result = remove(path.path().c_str());
    test(result != 0, "Locked file was deleted.");
  }
  result = remove(path.path().c_str());
  test(result == 0, "Unlocked file could not be deleted.");
}

//=============================================================================
void utest_lock_file::test_multiple_lock()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    std::shared_ptr<Error> error;
    LockedFile lock(path, error);
    assert(!error);
    LockedFile second_lock(path, error);
    test(!!error, "Error expected.");
    Error* err = error.get();
    test(dynamic_cast<LockFileError*>(err), "Wrong error type.");
  }
  result = remove(path.path().c_str());
  test(result == 0, "Unlocked file could not be deleted.");
}

//=============================================================================
int main() {
  utest_lock_file test;
  test.run_tests();
  return 0;
}

#include <Windows.h>

//=============================================================================
struct FileHandle
{
  HANDLE handle;
};

//=============================================================================
LockedFile::LockedFile(Path path, std::shared_ptr<Error>& error)
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
      error = std::shared_ptr<Error>(new LockFileError(path));
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
      error = std::shared_ptr<Error>(new GenericError(error_message));
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
void LockedFile::write(std::string contents)
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
  DWORD to_write = std::max<DWORD>(file_size.LowPart, contents.size());
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
std::string LockedFile::read() const
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
LockedFile::~LockedFile()
{
  CloseHandle(m_file_handle->handle);
}

//=============================================================================
void LockedFile::reset_file_pointer() const
{
  SetFilePointer(
    m_file_handle->handle, // HANDLE hFile,
    0,                     // LONG lDistanceToMove,
    NULL,                  // PLONG lpDistanceToMoveHigh,
    FILE_BEGIN             // DWORD dwMoveMethod
  );
}

//=============================================================================
Error::Error()
{
}

//=============================================================================
Error::~Error()
{
}

//=============================================================================
LockFileError::LockFileError(Path path)
  : m_path(path)
{
}

//=============================================================================
std::string LockFileError::to_string() const
{
  return
    std::string("File \"") +
    m_path.path() +
    std::string("\" could not be locked. Another process may be using it.");
}

//=============================================================================
LockFileError::~LockFileError()
{
}

//=============================================================================
GenericError::GenericError(std::string error)
  : m_error(error)
{
}

//=============================================================================
std::string GenericError::to_string() const
{
  return m_error;
}

//=============================================================================
GenericError::~GenericError()
{
}

#else //#ifdef __CYGWIN__

int main(int num_arguments, char* arguments[])
{
  return 0;
}

#endif //#ifdef __CYGWIN__
