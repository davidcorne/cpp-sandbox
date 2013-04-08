#include <iostream>

using namespace std;

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
  cout << "one < two " << (one < two) << endl;
  cout << "one == one " << (one == one) <<endl;
  cout << "two < two " << (two < two) <<endl;
  cout << "three < two " << (three < two) << endl;
  cout << "one < three " << (one < three) <<endl;
  cout << "three > two " << (three > two) << endl;
  return 0;
}
