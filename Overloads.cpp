//=============================================================================
//
// Looking at what happens if you have two classes with operators

#include <iostream>

using namespace std;

//=============================================================================
class Base_1 {
public:
  bool operator==(const Base_1& other)
    {
      return true;
    }
};

//=============================================================================
class Base_2 {
public:
  bool operator==(const Base_2& other)
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
  cout << (d1.Base_1::operator==(d2)) << endl;
  cout << (d1.Base_2::operator==(d2)) << endl;
  return 0;
}
