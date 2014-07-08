//=============================================================================
//
// 

#include <map>
#include <string>
#include <functional>

#include "Printer.h"

//=============================================================================
template <typename... Args>
void print(Args... arguments)
{
  Printer(std::cout).print(arguments...);
}

//=============================================================================
class Primitive {
public:

  class WrongTypeException{};
  
  Primitive();
  ~Primitive() = default;

  double d() const;
  Primitive& d(double d);
  
  std::string s() const;
  Primitive& s(std::string s);
  
  int i() const;
  Primitive& i(int i);

private:
  
  enum Type {
    TypeDouble,
    TypeString,
    TypeInt,
    TypeUnknown
  };

  friend std::ostream& operator<<(std::ostream&, const Primitive&);
  void validate_type(Type type) const;
  
  Type m_type;
  double m_double;
  int m_int;
  std::string m_string;
};

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Primitive& p)
{
  Primitive::Type type = p.m_type;
  if (type == Primitive::TypeDouble) {
    os << p.d();
  } else if (type == Primitive::TypeString) {
    os << p.s();
  } else if (type == Primitive::TypeInt) {
    os << p.i();
  }
  return os;
}

//=============================================================================
Primitive::Primitive()
  : m_type(TypeUnknown),
    m_double(0),
    m_int(0),
    m_string()
{
}

//=============================================================================
double Primitive::d() const
{
  validate_type(TypeDouble);
  return m_double;
}

//=============================================================================
Primitive& Primitive::d(double d)
{
  m_type = TypeDouble;
  m_double = d;
  return *this;
}

//=============================================================================
int Primitive::i() const
{
  validate_type(TypeInt);
  return m_int;
}

//=============================================================================
Primitive& Primitive::i(int i)
{
  m_type = TypeInt;
  m_int = i;
  return *this;
}

//=============================================================================
std::string Primitive::s() const
{
  validate_type(TypeString);
  return m_string;
}

//=============================================================================
Primitive& Primitive::s(std::string string)
{
  m_type = TypeString;
  m_string = string;
  return *this;
}

//=============================================================================
void Primitive::validate_type(Type type) const
{
  if (type != m_type) {
    throw WrongTypeException();
  }
}

class Object;
typedef std::function<Primitive(Object&, Object&)> Method;
typedef std::function<Primitive(Object&)> BoundMethod;

//=============================================================================
class Object {
public:

  Object() = default;

  Object(const Object&) = default;
  Object& operator=(const Object&) = default;

  ~Object() = default;
  
  Primitive& operator[](std::string property_name);
  const Primitive& operator[](std::string property_name) const;
  
  BoundMethod operator()(std::string method_name);
  Method& set_method(std::string method_name);
  
private:

  std::map<std::string, Primitive> m_properties;
  std::map<std::string, Method> m_methods;
};

//=============================================================================
Primitive& Object::operator[](std::string property_name)
{
  return m_properties[property_name];
}

//=============================================================================
const Primitive& Object::operator[](std::string property_name) const
{
  return m_properties.at(property_name);
}

//=============================================================================
Method& Object::set_method(std::string method_name)
{
  return m_methods[method_name];
}

//=============================================================================
BoundMethod Object::operator()(std::string method_name)
{
  return std::bind(m_methods[method_name], *this, std::placeholders::_1);
}

