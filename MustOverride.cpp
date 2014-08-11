#include <iostream>

//=============================================================================
class Base {
public:

  Base(int data)
    : m_data(data)
    {}
    
  virtual int get() = 0;
  
  virtual ~Base() = 0;
  
private:
  int m_data;
};

//=============================================================================
Base::~Base()
{
}

//=============================================================================
int Base::get()
{
  return m_data;
}

//=============================================================================
class Derived : public Base {
public:
  Derived(int data)
    : Base(data)
    {}
  
  virtual int get() {
    return Base::get();
  }
  
  ~Derived() {
  }
  
};

int main() {

  Derived derived(4);
  std::cout << derived.get() << std::endl;
  return 0;
}
