#include <iostream>

#include "Capabilities.h"
#if CAPABILITY_DIGRAPHS

//=============================================================================
class Example {
public:

  //===========================================================================
  // logic operators
  bool operator&&(const Example& t) {
    return true;
  }
  
  bool operator||(const Example& t) {
    return true;
  }
  
  bool operator!() {
    return true;
  }
  
  //===========================================================================
  // bitwise operators
  bool operator&(const Example& t) {
    return true;
  }
  
  bool operator|(const Example& t) {
    return true;
  }
  
  bool operator^(const Example& t) {
    return true;
  }
  
  bool operator~() {
    return true;
  }
  
  //===========================================================================
  // logic equals operators
  Example operator&=(const Example& t) {
    return t;
  }
  
  Example operator|=(const Example& t) {
    return t;
  }
  
  Example operator^=(const Example& t) {
    return t;
  }
  
  Example operator!=(const Example& t) {
    return t;
  }
  
};

//=============================================================================
int main() {
  bool a = true;
  bool b = true;
  if (a and b) {
    std::cout << "\"and\" is an operator.\n";
  }
  if (false or b) {
    std::cout << "\"or\" is also an operator.\n";
  }
  if (not false) {
    std::cout << "\"not\" is also an operator.\n";
  }

  Example t_1, t_2;
  if (t_1 and t_2) {
    std::cout << "\"and\" even works for classes\n";
  }
  
  if (t_1 or t_2) {
    std::cout << "\"or\" even works for classes\n";
  }
  
  if (not t_1) {
    std::cout << "\"and\" even works for classes\n";
  }
  
  if (t_1 bitand t_2) {
    std::cout << "\"bitand\" also works for classes\n";
  }
  
  if (t_1 bitor t_2) {
    std::cout << "\"bitor\" even works for classes\n";
  }
  
  if (compl t_1) {
    std::cout << "\"compl\" even works for classes\n";
  }
  
  if (t_1 xor t_2) {
    std::cout << "\"xor\" even works for classes\n";
  }
  
  t_1 and_eq t_2;
  std::cout << "\"and_eq\" even works for classes\n";
  
  t_1 or_eq t_2;
  std::cout << "\"or_eq\" even works for classes\n";
  
  t_1 xor_eq t_2;
  std::cout << "\"xor_eq\" even works for classes\n";
  std::cout.flush();
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif

