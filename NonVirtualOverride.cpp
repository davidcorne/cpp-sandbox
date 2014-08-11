// This is a small experiment about overriding methods without virtual, it
// works exactly how you'd expect. Works on stack based objects, not for
// pointers to the base class.
// 

#include <iostream>

//=============================================================================
class Parent {
public:

  void out() const {
    std::cout << "Parent" << std::endl;
  }
};

//=============================================================================
class Child : public Parent {
public:

  void out() const {
    std::cout << "Child" << std::endl;
  }
};

//=============================================================================
int main() {
  Parent p;
  p.out();
  Child c;
  c.out();

  Child* child = new Child;
  child->out();
  delete child;
  
  Parent* actually_a_child = new Child;
  actually_a_child->out();
  delete actually_a_child;
  return 0;
}
