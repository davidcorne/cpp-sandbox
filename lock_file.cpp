//=============================================================================
//
//D An RAII file locker. On creation, this will lock the file given.
//

#ifdef __CYGWIN__

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

#include <Windows.h>
// types: classes, enums, typedefs, namespaces

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class LockedFile {
public:

  LockedFile(std::string file);
  // Locks file

  HANDLE handle() const;
  // 

  ~LockedFile();
  // Unlocks the file

private:

  HANDLE m_file_handle;
};


//=============================================================================
LockedFile::LockedFile(std::string file)
{
  m_file_handle = CreateFile(
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
    m_file_handle, // HANDLE hFile,            
    &file_size     // PLARGE_INTEGER lpFileSize
  );
  assert(ok);

  OVERLAPPED sOverlapped;
  // lock the file

  ok = LockFileEx(
    m_file_handle,             // HANDLE hFile,
    LOCKFILE_EXCLUSIVE_LOCK |
    LOCKFILE_FAIL_IMMEDIATELY, // DWORD dwFlags,
    0,                         // DWORD dwReserved,
    file_size.LowPart,         // DWORD nNumberOfBytesToLockLow,
    file_size.HighPart,        // DWORD nNumberOfBytesToLockHigh,
    &sOverlapped               // LPOVERLAPPED lpOverlapped
  );
}

//=============================================================================
HANDLE LockedFile::handle() const
{
  return m_file_handle;
}

//=============================================================================
LockedFile::~LockedFile()
{
  CloseHandle(m_file_handle);
}

//=============================================================================
void write_file(std::string path)
{
  std::ofstream file_stream(path);
  file_stream << "Test file\n";
  file_stream.close();
}

//=============================================================================
int main(int num_arguments, char* arguments[])
//
//D The entry point and single function of this program
//
{
  // write a file
  std::string path("lock_file.txt");
  write_file(path);
  int result = 0;
  {
    LockedFile lock(path);
    result = remove(path.c_str());
    std::cout << "Locked file deleted? " << result << std::endl;
  }
  result = remove(path.c_str());
  std::cout << "Unlocked file deleted? " << result << std::endl;
  return EXIT_SUCCESS;
}

#else //#ifdef __CYGWIN__

int main(int num_arguments, char* arguments[])
{
  return EXIT_SUCCESS;
}

#endif //#ifdef __CYGWIN__
