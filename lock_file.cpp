//=============================================================================
//
//D An RAII file locker. On creation, this will lock the file given.
//

#ifdef __CYGWIN__

#include "UnitTest.h"

#include <assert.h>
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

  Error(std::string message);
  
  std::string to_string() const;

private:
  std::string m_message;
};

struct FileHandle;

//=============================================================================
class LockedFile {
public:

  LockedFile(std::string file);
  // Locks file

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
    test_read();
    test_write();
  }

private:

  void test_lock();
  void test_read();
  void test_write();
  void write_file(std::string path, std::string contents)
    {
      std::ofstream file_stream(path);
      file_stream << contents;
      file_stream.close();
    }

};

//=============================================================================
void utest_lock_file::test_write()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  std::string path("lock_file.txt");
  write_file(path, "");
  {
    LockedFile lock_file(path);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    std::string whole_file = lock_file.read();
    test(whole_file == new_contents, "Write incorrect.");
  }
  // Clean up
  int result = remove(path.c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_read()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  std::string path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    LockedFile lock_file(path);
    test(lock_file.read() == contents, "Contents is wrong.");
  }
  // Clean up
  int result = remove(path.c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_lock()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  std::string path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    LockedFile lock(path);
    result = remove(path.c_str());
    test(result != 0, "Locked file was deleted.");
  }
  result = remove(path.c_str());
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
LockedFile::LockedFile(std::string file)
  : m_file_handle(new FileHandle)
{
  m_file_handle->handle = CreateFile(
    file.c_str(),                 // LPCTSTR lpFileName,
    GENERIC_READ | GENERIC_WRITE, // DWORD dwDesiredAccess,
    FILE_SHARE_READ,              // DWORD dwShareMode,
    NULL,                         // LPSECURITY_ATTRIBUTES lpSecurityAttribs,
    OPEN_EXISTING,                // DWORD dwCreationDisposition,
    FILE_ATTRIBUTE_NORMAL,        // DWORD dwFlagsAndAttributes,
    NULL                          // HANDLE hTemplateFile
  );
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

//=============================================================================
void LockedFile::write(std::string contents)
{
  reset_file_pointer();
  DWORD bytes_written;
  WriteFile(
    m_file_handle->handle, // HANDLE hFile,
    contents.c_str(),      // LPCVOID lpBuffer,
    contents.size(),       // DWORD nNumberOfBytesToWrite,
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
Error::Error(std::string message)
  : m_message(message)
{
}

//=============================================================================
std::string Error::to_string() const
{
  return m_message;
}

#else //#ifdef __CYGWIN__

int main(int num_arguments, char* arguments[])
{
  return 0;
}

#endif //#ifdef __CYGWIN__
