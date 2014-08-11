// This only compiles with GCC 4.7 or higher
#if 1
// User defined literals
// more here
// http://akrzemi1.wordpress.com/2012/08/12/user-defined-literals-part-i/

// Note on constexpr
// The constexpr specifier declares that it is possible to evaluate the value
// of the function or variable at compile time. Such variables and functions
// can then be used where only compile time constant expressions are allowed.
// constexpr implies const.

#include <iostream>
#include <string>
#include <vector>

// cooked literal
class Binary
{
public:
  // like an ctor enum
  explicit Binary(const char* representation)
    : m_rep(representation)
    {}

  void print() const
    {
      std::cout << "I am: " << m_rep << std::endl;
    }
private:

  Binary();

  std::string m_rep;
};

// <nnn> Binary operator"" _b(const char* number)
// <nnn> {
// <nnn>   return Binary(number);
// <nnn> }

int main()
{
  Binary two("10");
  two.print();
  return 0;
}
#else
int main()
{
  return 0;
}
#endif

