#include <iostream>

//=============================================================================
class IntCompare {
public:
  IntCompare(int data)
    : m_data(data)
    {
    }

  bool operator<(const IntCompare&) const;
  bool operator<=(const IntCompare&) const;
  bool operator==(const IntCompare&) const;
  bool operator!=(const IntCompare&) const;
  bool operator>=(const IntCompare&) const;
  bool operator>(const IntCompare&) const;
  
private:
  double compare(const IntCompare& other) const;
  // returns:
  // -ve if other < this
  // 0 if other == this
  // +ve if other > this

  int m_data;
};

//=============================================================================
bool IntCompare::operator<(const IntCompare& other) const
{
  return compare(other) < 0;
}
  
//=============================================================================
bool IntCompare::operator<=(const IntCompare& other) const
{
  return compare(other) <= 0;
}
  
//=============================================================================
bool IntCompare::operator==(const IntCompare& other) const
{
  return compare(other) == 0;
}
  
//=============================================================================
bool IntCompare::operator>=(const IntCompare& other) const
{
  return compare(other) >= 0;
}
  
//=============================================================================
bool IntCompare::operator>(const IntCompare& other) const
{
  return compare(other) > 0;
}

//=============================================================================
double IntCompare::compare(const IntCompare& other) const
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
  std::cout << "one == one " << (one == one) << std::endl;
  std::cout << "two < two " << (two < two) << std::endl;
  std::cout << "three < two " << (three < two) << std::endl;
  std::cout << "one < three " << (one < three) << std::endl;
  std::cout << "three > two " << (three > two) << std::endl;
  return 0;
}
