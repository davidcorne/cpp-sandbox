// calling operators

#include <iostream>

class Foo {
public:

  void operator()() {
    std::cout << "operator() called." << std::endl;
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
