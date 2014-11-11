//=============================================================================

#ifndef Error_H
#define Error_H

#include <string>
#include <memory>

//=============================================================================
class Error {
public:

  Error();
  
  virtual std::string to_string() const = 0;

  virtual ~Error() = 0;
};

typedef std::shared_ptr<Error> ErrorPtr;

//----- Source
//=============================================================================
Error::Error()
{
}

//=============================================================================
Error::~Error()
{
}

#endif
