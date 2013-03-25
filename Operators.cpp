// calling operators

#include <iostream>

using namespace std;

class Foo {
public:

  void operator()() {
    cout << "operator() called." << endl;
  };
};

int main() {
  Foo* f = new Foo();
  (*f)();
  (*f).operator()();
  f->operator()();

  delete f;
  return 0;
}
