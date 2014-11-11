//=============================================================================

#include "Capabilities.h"
#if CAPABILITY_VARIADIC_TEMPLATES

#include <iostream>
#include <string>

//=============================================================================
class Base1 {
public:

  Base1(int i)
    {}

};

//=============================================================================
class Base2 {
public:

  Base2(int i, int j)
    {}

};

template <class Base, typename... Args>
class Mixin : public Base {
public:
  Mixin(std::string s, Args... arguments)
    : Base(arguments...)
    {}

};

//=============================================================================
int main()
{
  Mixin<Base1, int> m1("hi", 0);
  Mixin<Base2, int, int> m2("hi", 0, 1);
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif
