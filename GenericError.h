//=============================================================================
// This isn't the idea of the Error class, you should have a different derived
// class for each error. But this is only a messing around area.

#ifndef GenericError_H
#define GenericError_H

#include "Error.h"

//=============================================================================
class GenericError : public Error {
public:
  GenericError(std::string error);

  virtual std::string to_string() const;

  virtual ~GenericError();
  
private:
  std::string m_error;
};


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

#endif
