//=============================================================================
//
// This is a conditional templatised input function.

#include "Capabilities.h"
#if CAPABILITY_GENERIC_LAMBDAS

#include <iostream>
#include <string>
#include <sstream>
#include <functional>

//=============================================================================
template <typename T>
T input(
  std::string type_description,
  std::function<bool(T)> condition = [](const T& t)->bool{return true;}
)
{
  std::string in("");
  T t;
  while (true) {
    std::cout << "Plese enter a valid " << type_description << ": ";
    std::getline(std::cin, in);
    std::stringstream ss(in);
    if (ss >> t) {
      if (condition(t)) {
        break;
      }
    }
    std::cout
      << "\""
      << ss.str()
      << "\" is not a valid "
      << type_description
      << " please try again."
      << std::endl;
  }
  return t;
}

//=============================================================================
bool valid(const int& i)
{
  return 0 <= i && i <= 50;
}

//=============================================================================
int main()
{
  int i = input<int>("number");
  std::cout << i << std::endl;
  
  i = input<int>("number", valid);
  std::cout << i << std::endl;
  
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif
