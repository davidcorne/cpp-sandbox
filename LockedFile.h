//=============================================================================
// A locked file.

#ifndef LockedFile_H
#define LockedFile_H

#include "Path.h"
#include "Error.h"

class LockedFileImpl;

//=============================================================================
class LockedFile {
public:

  LockedFile(Path file, ErrorPtr& error);
  // Locks file.

  std::string read() const;
  
  void write(std::string contents);
  
  ~LockedFile();
  // Unlocks the file

private:
  std::unique_ptr<LockedFileImpl> m_impl;
};

//----- Source

#include "LockedFileImpl.h"

//=============================================================================
LockedFile::LockedFile(Path path, ErrorPtr& error)
  : m_impl(nullptr)
{
  m_impl = lock_file(path, error);
}

//=============================================================================
void LockedFile::write(std::string contents)
{
  assert(m_impl);
  m_impl->write(contents);
}

//=============================================================================
std::string LockedFile::read() const
{
  assert(m_impl);
  return m_impl->read();
}

//=============================================================================
LockedFile::~LockedFile()
{
  m_impl = nullptr;
}

#endif
