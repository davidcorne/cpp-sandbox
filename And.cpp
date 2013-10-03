//
// 

#include <iostream>

using namespace std;

//=============================================================================
class T {
public:

  //===========================================================================
  // logic operators
  bool operator&&(const T& t) {
    return true;
  }
  
  bool operator||(const T& t) {
    return true;
  }
  
  bool operator!() {
    return true;
  }
  
  //===========================================================================
  // bitwise operators
  bool operator&(const T& t) {
    return true;
  }
  
  bool operator|(const T& t) {
    return true;
  }
  
  bool operator^(const T& t) {
    return true;
  }
  
  bool operator~() {
    return true;
  }
  
  //===========================================================================
  // logic operators
  T operator&=(const T& t) {
    return t;
  }
  
  T operator|=(const T& t) {
    return t;
  }
  
  T operator^=(const T& t) {
    return t;
  }
  
  T operator!=(const T& t) {
    return t;
  }
  
};

//=============================================================================
int main() {
  bool a = true;
  bool b = true;
  if (a and b) {
    cout << "\"and\" is an operator." << endl;
  }
  if (false or b) {
    cout << "\"or\" is also an operator." << endl;
  }
  if (not false) {
    cout << "\"not\" is also an operator." << endl;
  }

  T t_1, t_2;
  if (t_1 and t_2) {
    cout << "\"and\" even works for classes" << endl;
  }
  
  if (t_1 or t_2) {
    cout << "\"or\" even works for classes" << endl;
  }
  
  if (not t_1) {
    cout << "\"and\" even works for classes" << endl;
  }
  
  if (t_1 bitand t_2) {
    cout << "\"bitand\" also works for classes" << endl;
  }
  
  if (t_1 bitor t_2) {
    cout << "\"bitor\" even works for classes" << endl;
  }
  
  if (compl t_1) {
    cout << "\"compl\" even works for classes" << endl;
  }
  
  if (t_1 xor t_2) {
    cout << "\"xor\" even works for classes" << endl;
  }
  
  t_1 and_eq t_2;
  cout << "\"and_eq\" even works for classes" << endl;
  
  t_1 or_eq t_2;
  cout << "\"or_eq\" even works for classes" << endl;
  
  t_1 xor_eq t_2;
  cout << "\"xor_eq\" even works for classes" << endl;

  return 0;
}
