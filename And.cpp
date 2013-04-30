//
// 

#include <iostream>

using namespace std;

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
  return 0;
}
