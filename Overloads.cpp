//=============================================================================
//
// Looking at what happens if you have two classes with operators

#include <iostream>

//=============================================================================
class Base_1 {
public:
  bool operator==(const Base_1&)
    {
      return true;
    }
};

//=============================================================================
class Base_2 {
public:
  bool operator==(const Base_2&)
    {
      return false;
    }
};

//=============================================================================
class Derived : public Base_1, public Base_2 {
public:

};

int main() {
  Derived d1;
  Derived d2;
  // d1 == d2;
  // gives
  // request for member 'operator==' is ambiguous
  // candidates are: bool Base_2::operator==(const Base_2&)
  //                 bool Base_1::operator==(const Base_1&)
  std::cout << (d1.Base_1::operator==(d2)) << std::endl;
  std::cout << (d1.Base_2::operator==(d2)) << std::endl;
  return 0;
}
