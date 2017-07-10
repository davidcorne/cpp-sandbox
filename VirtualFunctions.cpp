//=============================================================================
// How virtual functions work in constructors and destructors

#include <iostream>

//=============================================================================
class Base {
public:

  Base()
    {
      print("Base::Base()");
      function();
    }

  virtual void function() const
    {
      print("Base::function()");
    }

  virtual ~Base()
    {
      print("Base::~Base()");
      function();
    }
protected:

  void print(const char* to_print) const
    {
      std::cout << to_print << std::endl;
    }
};

//=============================================================================
class Derived : public Base {
public:

  Derived()
    : Base()
    {
      print("Derived::Derived()");
      function();
    }

  virtual void function() const override
    {
      print("Derived::function()");
    }

  virtual ~Derived()
    {
      print("Derived::~Derived()");
      function();
    }
};

//=============================================================================
int main()
{
  Derived d;
  return 0;
}
