//
// 

#include <iostream>
#include <memory>

using namespace std;

//=============================================================================
class Foo {
public:

  Foo() {}
  ~Foo() {cout << "Foo deleted." << endl;}

};

int main() {
  while (true) {
    Foo* f = new Foo();
  }
  return 0;
}
