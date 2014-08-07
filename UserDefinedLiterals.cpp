// This only compiles with GCC 4.7 or higher
// User defined literals
// more here
// http://akrzemi1.wordpress.com/2012/08/12/user-defined-literals-part-i/

// Note on constexpr
// The constexpr specifier declares that it is possible to evaluate the value
// of the function or variable at compile time. Such variables and functions
// can then be used where only compile time constant expressions are allowed.
// constexpr implies const.

#include <iostream>

// cooked literal
//=============================================================================
class Length {
public:
  
  static Length InMillimeters(double millimeters);
  
  static Length InInches(double inches);

private:

  friend std::ostream& operator<<(std::ostream& os, Length length);
  
  explicit Length(double length_in_millimeters);
  
  double m_length;
  // in mm
};

// non-member operators
std::ostream& operator<<(std::ostream& os, Length length);

// User Defined Literals
Length operator"" _mm(long double mil);
Length operator"" _mm(unsigned long long mil);
Length operator"" _inches(long double mil);
Length operator"" _inches(unsigned long long mil);

//=============================================================================
int main()
{
  Length l = 14.3_mm;
  std::cout << "My length is: " << l << std::endl;

  l = 15_mm;
  std::cout << "My length is: " << l << std::endl;

  l = 14.3_inches;
  std::cout << "My length is: " << l << std::endl;

  l = 15_inches;
  std::cout << "My length is: " << l << std::endl;

  return 0;
}

//=============================================================================
Length Length::InMillimeters(double millimeters)
{
  return Length(millimeters);
}

//=============================================================================
Length Length::InInches(double inches)
{
  return Length(inches * 25.4);
}

//=============================================================================
Length::Length(double length_in_millimeters)
  : m_length(length_in_millimeters)
{
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, Length length)
{
  os << length.m_length;
  return os;
}

//=============================================================================
Length operator"" _mm(long double mil)
{
  return Length::InMillimeters(static_cast<double>(mil));
}

//=============================================================================
Length operator"" _mm(unsigned long long mil)
// the integer version
{
  return Length::InMillimeters(static_cast<double>(mil));
}

//=============================================================================
Length operator"" _inches(long double mil)
{
  return Length::InInches(static_cast<double>(mil));
}

//=============================================================================
Length operator"" _inches(unsigned long long mil)
// the integer version
{
  return Length::InInches(static_cast<double>(mil));
}


