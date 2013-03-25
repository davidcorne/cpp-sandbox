// Trying to copy a reference

#include <iostream>

using namespace std;

class Foo
{
public:
  Foo()
    : member(0)
    {}
    
  int member;
  void out() const {
    cout << member << endl;
  }
private:
  Foo(const Foo&);
  void operator=(const Foo&);
};
  
int main() {
  Foo f;
  Foo& g = f;
  g.member = 6;
  f.out();
  g.out();
  return 0;
}
