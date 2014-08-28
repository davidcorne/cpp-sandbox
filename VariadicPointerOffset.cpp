//=============================================================================
//
// Quite a complicated file. I was trying to use variadic templates to access
// private methods of a class. Hopefully not of any practical use (it breaks
// encapsulation and is extremely fragile) but an interesting idea to try, 

#include <iostream>
// #include <const char*>

#pragma clang diagnostic ignored "-Wunused-private-field"

//=============================================================================
class Bank {
public:

  Bank(int money)
    : m_money(money),
      m_thing("I'm a const char*."),
      another_thing(-5.3234)
    {}

  void show_balance() {
    std::cout << "Your balance is: " << m_money << std::endl;
    std::cout << "thing: " << m_thing << std::endl;
    std::cout << "another thing: " << another_thing << std::endl << std::endl;
  }

private:
  int m_money;
  const char* m_thing;
  double another_thing;
};

class Other {
public:

  Other()
    : m_a(9999999),
      m_b("this or that"),
      m_c(5.423434),
      m_bank(40)
    {}
private:

  int m_a;
  std::string m_b;
  double m_c;
  Bank m_bank;
};

//=============================================================================
template<typename IN, typename OUT>
OUT* change(IN* input)
{
  OUT* new_ptr = reinterpret_cast<OUT*>(input);
  --new_ptr;
  return new_ptr;
}

//=============================================================================
template<typename IN, typename OUT, typename FIRST, typename... ARGS>
//
//D Will return a pointer of type OUT to the member that many up the list.
//D
//D e.g
// if there was the following class
//
// class Foo {
// private:
//   int    m_1;
//   long   m_2;
//   float  m_3;
//   double m_4;
//   bool   m_5;
// };
//
// then you can access m_1 in the following way
// Foo foo;
// Foo* foo_ptr = &foo;
// ++foo_ptr;
// int* int_ptr = change<Foo, int, long, float, double, bool>(foo_ptr);

OUT* change(IN* input)
{
  FIRST* new_ptr = reinterpret_cast<FIRST*>(input);
  --new_ptr;
  OUT* ptr = change<FIRST, OUT, ARGS...>(new_ptr);
  return ptr;
}

class Foo {
public:
  Foo()
    : m_1(1),
      m_2(2),
      m_3(3.0),
      m_4(4.0),
      m_5(true)
    {}
  
 private:
   int    m_1;
   long   m_2;
   float  m_3;
   double m_4;
   bool   m_5;
};
  
//=============================================================================
int main() {
  Bank my_bank(14);
  my_bank.show_balance();

  // make a pointer referencing my_bank
  Bank* ptr;
  ptr = &my_bank;

  // increments by sizeof(Bank) to get to the end of the class
  ++ptr;

  int* i_ptr = change<Bank, int, double, const char*>(ptr);
  *i_ptr = 2000;
  std::cout << std::endl;
  my_bank.show_balance();

  // <nnn> // a new test
  // <nnn> Other o;
  // <nnn> Other* other_ptr;
  // <nnn> other_ptr = &o;
  // <nnn> ++other_ptr;
  // <nnn> double* d_ptr = change<Other, double, int, string, Bank>(other_ptr);
  // <nnn> cout << *d_ptr << endl;

  
  Foo foo;
  Foo* foo_ptr = &foo;
  ++foo_ptr;
  int* int_ptr = change<Foo, int, long, float, double, bool>(foo_ptr);
  std::cout << *int_ptr << std::endl;
  return 0;
}
