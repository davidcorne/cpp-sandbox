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

  Primitive(const Primitive&) = default;
  Primitive& operator=(const Primitive&) = default;
  
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

  std::string type_to_string(Type type) const;
  
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
    print(
      "Wrong type, expecting ",
      type_to_string(type),
      " got ",
      type_to_string(m_type)
    );
    throw WrongTypeException();
  }
}

//=============================================================================
std::string Primitive::type_to_string(Type type) const
{
  std::string type_string;
  if (type == Primitive::TypeDouble) {
    type_string = "double";
  } else if (type == Primitive::TypeString) {
    type_string = "string";
  } else if (type == Primitive::TypeInt) {
    type_string = "int";
  } else if (type == Primitive::TypeUnknown) {
    type_string = "unknown";
  }
  return type_string;
}

class Object;
typedef std::function<Primitive(Object&, Object&)> Method;
typedef std::function<Primitive(Object&)> BoundMethod;

//=============================================================================
class Object {
public:

  Object() = default;

  //----- Moveable type
  Object(Object&&) = default;
  Object& operator=(Object&&) = default;
  
  ~Object() = default;

  Object clone() const;
  
  Primitive& operator[](std::string property_name);
  const Primitive& operator[](std::string property_name) const;
  
  BoundMethod operator()(std::string method_name);
  Method& set_method(std::string method_name);
  
private:

  Object(const Object&) = delete;
  Object& operator=(const Object&) = delete;

  std::map<std::string, Primitive> m_properties;
  std::map<std::string, Method> m_methods;
};

//=============================================================================
Object Object::clone() const
{
  Object o;
  o.m_properties = m_properties;
  o.m_methods = m_methods;
  return std::move(o);
}

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
  return [this, method_name](Object& o) -> Primitive {
    return m_methods[method_name](*this, o);
  };
}

