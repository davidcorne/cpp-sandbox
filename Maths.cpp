//=============================================================================
#include <iostream>

//=============================================================================
template <typename U, typename V>
auto add(const U& u, const V& v) -> decltype(u+v);

//=============================================================================
class MyInt {
public:

  MyInt(int i);
  ~MyInt();

  int operator+(const MyInt& other) const;
  
private:
  int m_i;
};

//=============================================================================
int main()
{
  MyInt five(5);
  MyInt six(6);
  std::cout << add(five, six) << std::endl;
}

//=============================================================================
MyInt::MyInt(int i)
  : m_i(i)
{
}

//=============================================================================
MyInt::~MyInt() = default;

//=============================================================================
int MyInt::operator+(const MyInt& other) const
{
  return m_i + other.m_i;
}

//=============================================================================
template <typename U, typename V>
auto add(const U& u, const V& v) -> decltype(u+v)
{
  return u+v;
}
