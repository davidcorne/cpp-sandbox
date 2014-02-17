//=============================================================================
//
// Idea from http://www.drdobbs.com/cpp/mixin-based-programming-in-c/184404445
 

#include <iostream>
#include <string>

#include "compiler_guards.h"

using namespace std;

#if CPP_ELEVEN_SUPPORTED

//=============================================================================
class Printable {
public:

  Printable() {}
  virtual ~Printable() = 0;

  void print() const
    {
      cout << to_str() << endl;
    }
  
private:

  virtual string to_str() const = 0;
};

//=============================================================================
Printable::~Printable()
{}

//=============================================================================
class Customer : public Printable {
public:

  Customer(string first_name, string last_name)
    : m_first_name(first_name),
      m_last_name(last_name)
    {}

  ~Customer() {}
        
protected:
  virtual string to_str() const override
    {
      string self("Name: ");
      self += m_first_name;
      self += " ";
      self += m_last_name;
      return self;
    }
  
private:
  string m_first_name;
  string m_last_name;
};

//=============================================================================
class Company : public Printable {
public:

  Company(string company_name)
    : m_company_name(company_name)
    {}

  ~Company() {}
        
protected:
  virtual string to_str() const override
    {
      string self("Company Name: ");
      self += m_company_name;
      return self;
    }
  
private:
  Company(Company&);
  Company& operator=(const Company&);
  
  string m_company_name;
};

//=============================================================================
template <class Base, class... Args>
class PhoneContact : public Base {
public:

  PhoneContact(Args... arguments, string phone_number)
    : Base(arguments...),
      m_phone_number(phone_number)
    {}

  ~PhoneContact() {}

protected:

  virtual string to_str() const override
    {
      return Base::to_str() + ", Phone: " + m_phone_number;
    }

private:
  PhoneContact(PhoneContact&);
  PhoneContact& operator=(const PhoneContact&);
  

  string m_phone_number;
};
  
//=============================================================================
template <class Base, class... Args>
class EmailContact : public Base {
public:

  EmailContact(Args... arguments, string email_address)
    : Base(arguments...),
      m_email_address(email_address)
    {}

  ~EmailContact() {}

protected:

  virtual string to_str() const override
    {
      return Base::to_str() + ", Email: " + m_email_address;
    }

private:
  EmailContact(EmailContact&);
  EmailContact& operator=(const EmailContact&);
  

  string m_email_address;
};

typedef PhoneContact<Customer, string, string> CustomerPhoneContact;
typedef EmailContact<Customer, string, string> CustomerEmailContact;

//=============================================================================
int main() {
  Customer pete("Peter", "Calderson");
  pete.print();
  CustomerPhoneContact dave("David", "Corne", "01254 453873");
  dave.print();
  CustomerEmailContact tim("Tim", "Timson", "tim_timson@gmail.com");
  tim.print();
  PhoneContact<Company, string> delcam("Delcam", "01254 453873");
  delcam.print();

  EmailContact<CustomerPhoneContact, string, string, string> me(
    "David", "Corne", "07921143821", "davidcorne@gmail.com"
  );
  me.print();
  return 0;
}

#else // CPP_ELEVEN_SUPPORTED
NOT_SUPPORTED_MAIN
#endif // CPP_ELEVEN_SUPPORTED
