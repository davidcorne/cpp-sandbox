//=============================================================================
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "Dictionary.h"

class Instance;

//=============================================================================
typedef std::function<Instance(Instance&)> MemberFunction;

//=============================================================================
class Type {
public:

  Type(std::string name);

  ~Type();
  
  std::string name() const;

  void add_function(
    std::string function_name,
    MemberFunction member_function
  );

  template <typename PRIMITIVE>
  void add_primitive(std::string data_name, PRIMITIVE value);

private:
  
  friend class Instance;
  friend class TypeLibrary;
  
  std::string m_name;
  Dictionary m_dict;
};

//=============================================================================
bool operator==(const Type& a, const Type& b);

//=============================================================================
class Instance {
public:

  Instance(Type type);
  ~Instance();
  
  Type type() const;

  MemberFunction operator[](std::string function_name);

  
  std::string repr() const;
  // A string representation of the instance.
  
private:

  Type m_type;
};

//=============================================================================
template <typename PRIMITIVE>
class Primitive {
public:
  
  Primitive(PRIMITIVE value);

  ~Primitive();
  
  PRIMITIVE value() const;

  void set_value(PRIMITIVE value);

  operator Instance() const;
  
private:

  Type type() const;

  PRIMITIVE m_value;
};

//=============================================================================
class TypeLibrary {
public:

  static void register_type(Type type);

  static bool type_registered(std::string type_name);
  
  static Instance construct_instance(std::string type_name);

  template <typename PRIMITIVE>
  static Primitive<PRIMITIVE> primitive(PRIMITIVE value);
  
private:

  static std::vector<Type>::iterator find(std::string type);
  
  TypeLibrary();
  ~TypeLibrary();

  static std::vector<Type> s_type_library;
};

//----- Somehow user defined stuff.

//=============================================================================
class FactorialRunFunction {
public:

  Instance operator()(Instance& i);
};

// <nnn> //=============================================================================
// <nnn> Instance FactorialRunFunction::operator()(Instance& i)
// <nnn> {
// <nnn>   Primitive<int> out = TypeLibrary::primitive<int>(0);
// <nnn>   if (i
// <nnn> }

//=============================================================================
int main()
{
  // <nnn> Type factorial_class("factorial");
  // <nnn> factorial_class.add_function("run", FactorialRunFunction());
  // <nnn> TypeLibrary::register_type(factorial_class);
  
  // <nnn> Instance factorial = TypeLibrary::construct_instance("factorial");
  // <nnn> Instance five = TypeLibrary::primitive<int>(5);
  // <nnn> Instance result = factorial["run"](five);
  // <nnn> std::cout << result.repr() << std::endl;
}

//=============================================================================
//-----Implementation.

//----- Type
//=============================================================================
Type::Type(std::string name)
  : m_name(name),
    m_dict()
{
}

//=============================================================================
Type::~Type() = default;

//=============================================================================
std::string Type::name() const
{
  return m_name;
}

//=============================================================================
void Type::add_function(
  std::string function_name,
  MemberFunction member_function
)
{
  m_dict.set_item(function_name, member_function);
}

//=============================================================================
template <typename PRIMITIVE>
void Type::add_primitive(std::string data_name, PRIMITIVE value)
{
  m_dict.set_item(data_name, value);
}

//=============================================================================
bool operator==(const Type& a, const Type& b)
{
  return a.name() == b.name();
}

//------ TypeLibrary
std::vector< Type> TypeLibrary::s_type_library;

//=============================================================================
void TypeLibrary::register_type(Type type)
{
  auto it = find(type.name());
  if (it == std::end(s_type_library)) {
    s_type_library.erase(it);
  }
  s_type_library.push_back(type);
}

//=============================================================================
bool TypeLibrary::type_registered(std::string type_name)
{
  return find(type_name) != std::end(s_type_library);
}

//=============================================================================
Instance TypeLibrary::construct_instance(std::string type_name)
{
  assert(type_registered(type_name) && "Type not registered");
  auto it = find(type_name);
  return Instance(*it);
}

//=============================================================================
template <typename PRIMITIVE>
Primitive<PRIMITIVE> TypeLibrary::primitive(PRIMITIVE value)
{
  return Primitive<PRIMITIVE>(value);
}

//=============================================================================
std::vector<Type>::iterator TypeLibrary::find(std::string type_name)
{
  return std::find_if(
    std::begin(s_type_library),
    std::end(s_type_library),
    [type_name](Type type)->bool{return type.name() == type_name;}
  );
}

//----- Instance

//=============================================================================
Instance::Instance(Type type)
  : m_type(type)
{
}

//=============================================================================
Instance::~Instance()
{
}

//=============================================================================
MemberFunction Instance::operator[](std::string function_name)
{
  return m_type.m_dict.item<MemberFunction>(function_name);
}

//=============================================================================
Type Instance::type() const
{
  return m_type;
}

//=============================================================================
std::string Instance::repr() const
{
  return "// <nnn> ";
}

//----- Primitive

//=============================================================================
template <typename PRIMITIVE>
Primitive<PRIMITIVE>::Primitive(PRIMITIVE value)
  : m_value(value)
{
}

//=============================================================================
template <typename PRIMITIVE>
Primitive<PRIMITIVE>::~Primitive()
{
}

//=============================================================================
template <typename PRIMITIVE>
Primitive<PRIMITIVE>::operator Instance() const
{
  return Instance(type());
}

//=============================================================================
template <typename PRIMITIVE>
Type Primitive<PRIMITIVE>::type() const
{
  Type t("PRIMITIVE");
  // <nnn> t.add_function(
  return t;
}

