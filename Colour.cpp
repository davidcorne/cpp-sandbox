#include "Capabilities.h"

#ifdef CAPABILITY_USER_DEFINED_LITERALS
#include <iostream>
#include <limits>

#include <cassert>

template <char C>
class ColourComponent {
public:

  explicit ColourComponent(int i) : m_component(i) 
  {

  }

  int component() const { return m_component;}
private:

  int m_component;
};

template <char C>
std::ostream& operator<<(std::ostream& os, const ColourComponent<C>& component) {
    os << component.component();
    return os;
}

using Red = ColourComponent<'r'>;
Red operator""_red(unsigned long long i) {
  assert(i < std::numeric_limits<int>::max());
  return Red(static_cast<int>(i));
}
using Green = ColourComponent<'g'>;
Green operator""_green(unsigned long long i) {
  assert(i < std::numeric_limits<int>::max());
  return Green(static_cast<int>(i));
}
using Blue = ColourComponent<'b'>;
Blue operator""_blue(unsigned long long i) {
  assert(i < std::numeric_limits<int>::max());
  return Blue(static_cast<int>(i));
}
using Alpha = ColourComponent<'a'>;
Alpha operator""_alpha(unsigned long long i) {
  assert(i < std::numeric_limits<int>::max());
  return Alpha(static_cast<int>(i));
}
class Colour {
public:

  Colour(Red r, Green g, Blue b, Alpha a) 
    : m_r(r),
      m_g(g),
      m_b(b),
      m_a(a)
  {

  }

  void operator<<(std::ostream& os) const {
    os << m_r << " " << m_g << " " << m_b << " " << m_a;
  }
private:

  Red m_r;
  Green m_g;
  Blue m_b;
  Alpha m_a;
};

std::ostream& operator<<(std::ostream& os, const Colour& colour) {
  colour.operator<<(os);
  return os;
}

int main() {
  Colour c(150_red, 0_green, 255_blue, 100_alpha);
  std::cout << c << "\n";
  return 0;
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_USER_DEFINED_LITERALS);
#endif
