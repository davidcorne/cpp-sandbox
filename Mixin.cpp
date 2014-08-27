//=============================================================================
//
// Idea from http://www.drdobbs.com/cpp/mixin-based-programming-in-c/184404445
 

#include <iostream>
#include <string>

//=============================================================================
class Printable {
public:

  Printable() {}
  virtual ~Printable() = 0;

  void print() const
    {
      std::cout << to_str() << std::endl;
    }
  
private:

  virtual std::string to_str() const = 0;
};

//=============================================================================
Printable::~Printable()
{}

//=============================================================================
class Customer : public Printable {
public:

  Customer(std::string first_name, std::string last_name)
    : m_first_name(first_name),
      m_last_name(last_name)
    {}

  ~Customer() {}
        
protected:
  virtual std::string to_str() const override
    {
      std::string self("Name: ");
      self += m_first_name;
      self += " ";
      self += m_last_name;
      return self;
    }
  
private:
  std::string m_first_name;
  std::string m_last_name;
};

//=============================================================================
class Company : public Printable {
public:

  Company(std::string company_name)
    : m_company_name(company_name)
    {}

  ~Company() {}
        
protected:
  virtual std::string to_str() const override
    {
      std::string self("Company Name: ");
      self += m_company_name;
      return self;
    }
  
private:
  Company(Company&);
  Company& operator=(const Company&);
  
  std::string m_company_name;
};

//=============================================================================
template <class Base, class... Args>
class PhoneContact : public Base {
public:

  PhoneContact(Args... arguments, std::string phone_number)
    : Base(arguments...),
      m_phone_number(phone_number)
    {}

  ~PhoneContact() {}

protected:

  virtual std::string to_str() const override
    {
      return Base::to_str() + ", Phone: " + m_phone_number;
    }

private:
  PhoneContact(PhoneContact&);
  PhoneContact& operator=(const PhoneContact&);
  

  std::string m_phone_number;
};
  
//=============================================================================
template <class Base, class... Args>
class EmailContact : public Base {
public:

  EmailContact(Args... arguments, std::string email_address)
    : Base(arguments...),
      m_email_address(email_address)
    {}

  ~EmailContact() {}

protected:

  virtual std::string to_str() const override
    {
      return Base::to_str() + ", Email: " + m_email_address;
    }

private:
  EmailContact(EmailContact&);
  EmailContact& operator=(const EmailContact&);
  

  std::string m_email_address;
};

typedef PhoneContact<Customer, std::string, std::string> CustomerPhoneContact;
typedef EmailContact<Customer, std::string, std::string> CustomerEmailContact;

//=============================================================================
int main() {
  Customer pete("Peter", "Calderson");
  pete.print();
  CustomerPhoneContact dave("David", "Corne", "01254 453873");
  dave.print();
  CustomerEmailContact tim("Tim", "Timson", "tim_timson@gmail.com");
  tim.print();
  PhoneContact<Company, std::string> delcam("Delcam", "01254 453873");
  delcam.print();

  EmailContact<CustomerPhoneContact, std::string, std::string, std::string> me(
    "David", "Corne", "07921143821", "davidcorne@gmail.com"
  );
  me.print();
  return 0;
}
