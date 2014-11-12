
#define UNUSED_VARIABLE 1
#include "IgnoreDiagnostics.h"


#include <iostream>
#include <string>

//=============================================================================
class Exception {
public:

  virtual void raise();
  // Raise the exception.
  
  virtual ~Exception();

protected:

  Exception();

  Exception(const Exception& e);
  Exception& operator=(const Exception& e);

};

//=============================================================================
class GenericException : public Exception {
public:

  GenericException(std::string message);

  virtual void raise() override;

  std::string message() const;
  
  virtual ~GenericException();

private:
  
  std::string m_message;
};

//=============================================================================
class ReallySpecificException : public Exception {
public:

  ReallySpecificException();

  virtual void raise() override;

  virtual ~ReallySpecificException();

private:
  
};

//=============================================================================
void operation(int num, Exception& e)
{
  if (num < 0) {
    e.raise();
  } else {
    throw std::string("Hi");
  }
}

//=============================================================================
void caught_operation(int num, Exception& exception)
{
  try {
    operation(num, exception);
  } catch (GenericException& ge) {
    std::cout << ge.message() << std::endl;
  } catch (Exception& e) {
    std::cout << "A known exception was thrown." << std::endl;
  } catch (...) {
    std::cout << "An unknown error occured" << std::endl;
  }
}

//=============================================================================
int main()
{
  GenericException generic_exception("Should be called.");
  caught_operation(-1, generic_exception);
  ReallySpecificException exception;
  caught_operation(-1, exception);
  caught_operation(5, exception);
}

Exception::Exception()
{
}

Exception::~Exception() {}

Exception::Exception(const Exception&)
{
}

Exception& Exception::operator=(const Exception&)
{
  return *this;
}

void Exception::raise() {
  throw *this;
}

GenericException::GenericException(std::string message)
  : m_message(message)
{
}

GenericException::~GenericException() {}

void GenericException::raise()
{
  throw *this;
}

std::string GenericException::message() const
{
  return std::string("Exception: \"") + m_message + std::string("\"");
}

ReallySpecificException::ReallySpecificException() {}
ReallySpecificException::~ReallySpecificException() {}

void ReallySpecificException::raise()
{
  throw *this;
}
