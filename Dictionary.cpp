//=============================================================================
// The aim of this is to keep a python like dictionary, it will use strings
// for keys, but can store any copyable object.

#include "Dictionary.h"

//=============================================================================
class IntType {
public:

  IntType(int i);
  ~IntType();
  IntType(const IntType&);
  IntType& operator=(const IntType&);

  int value() const;
};

//=============================================================================
int main()
{
  Dictionary dict;
  dict.set_item("hi", 4);
  std::cout << dict.item<int>("hi") << std::endl;
  dict.set_item<std::string>("there", "THIS IS IN");
  std::cout << dict.item<std::string>("there") << std::endl;

  dict.set_item("hi", 4);
  std::cout << dict.item<int>("hi") << std::endl;
  dict.set_item("hi", 4.5);
  std::cout << dict.item<double>("hi") << std::endl;
  return 0;
}

