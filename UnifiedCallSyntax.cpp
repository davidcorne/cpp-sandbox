//=============================================================================
//
// The unified call syntax is described here
//   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4165.pdf
//
// this is an example which would stop working with the allow "this" in not
// only the first parameter location.

#include <iostream>

struct X {

};

struct Y {

};

void function(X x, Y y)
{
  std::cout << "x first." << std::endl;
}

void function(Y y, X x)
{
  std::cout << "y first." << std::endl;
}


//=============================================================================
int main(int argc, char** argv) 
{
  X x;
  Y y;
  function(x, y);
  function(y, x);
  // which would this do?
  // x.function(y)
  return 0;
}
