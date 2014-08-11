#include <iostream>

//=============================================================================
template <typename T>
class Compare {
public:

  Compare();
  // Ctor

  // all the comparison operators
  bool operator<(const T&) const;
  bool operator<=(const T&) const;
  bool operator==(const T&) const;
  bool operator!=(const T&) const;
  bool operator>=(const T&) const;
  bool operator>(const T&) const;

  virtual ~Compare() = 0;
  // pure virtual destructor
  
private:
  virtual int compare(const T& other) const = 0;
  // returns:
  // -ve if other < this
  // 0 if other == this
  // +ve if other > this
};

//=============================================================================
template <typename T>
Compare<T>::Compare()
{
}

//=============================================================================
template <typename T>
Compare<T>::~Compare()
{
}

//=============================================================================
template <typename T>
bool Compare<T>::operator<(const T& other) const
{
  return compare(other) < 0;
}
  
//=============================================================================
template <typename T>
bool Compare<T>::operator<=(const T& other) const
{
  return compare(other) <= 0;
}
  
//=============================================================================
template <typename T>
bool Compare<T>::operator==(const T& other) const
{
  return compare(other) == 0;
}
  
//=============================================================================
template <typename T>
bool Compare<T>::operator>=(const T& other) const
{
  return compare(other) >= 0;
}
  
//=============================================================================
template <typename T>
bool Compare<T>::operator>(const T& other) const
{
  return compare(other) > 0;
}

//=============================================================================
class IntCompare : public Compare<IntCompare> {
public:
  IntCompare(int data);

  virtual ~IntCompare();
  
private:
  int compare(const IntCompare& other) const;

  int m_data;
};

//=============================================================================
IntCompare::IntCompare(int data)
  : m_data(data)
{
}

//=============================================================================
IntCompare::~IntCompare()
{
}

//=============================================================================
int IntCompare::compare(const IntCompare& other) const
// returns:
// -ve if other < this
// 0 if other == this
// +ve if other > this
{
  // easy ordering because they're ints
  return m_data - other.m_data;
}
  
//=============================================================================
int main() {
  IntCompare one(1);
  IntCompare two(2);
  IntCompare three(3);
  std::cout << "one < two " << (one < two) << std::endl;
  std::cout << "one == one " << (one == one) <<std::endl;
  std::cout << "two < two " << (two < two) << std::endl;
  std::cout << "three < two " << (three < two) << std::endl;
  std::cout << "one < three " << (one < three) << std::endl;
  std::cout << "three > two " << (three > two) << std::endl;
  return 0;
}
