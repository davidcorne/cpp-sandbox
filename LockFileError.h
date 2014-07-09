//=============================================================================
// An error if a file has not been locked.

#ifndef LockFileError_H
#define LockFileError_H

//=============================================================================
class LockFileError : public Error {
public:
  
  LockFileError(Path path);

  virtual std::string to_string() const;

  virtual ~LockFileError();
  
private:
  Path m_path;
};

//----- Source

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

#endif
