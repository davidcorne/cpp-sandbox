// testing what bitwise (I think) Xor does

#include <iostream>

using namespace std;

int main() {
  
  cout << "0 ^ 0 = " << (0 ^ 0) << endl;
  cout << "0 ^ 1 = " << (0 ^ 1) << endl;
  cout << "1 ^ 0 = " << (1 ^ 0) << endl;
  cout << "1 ^ 1 = " << (1 ^ 1) << endl;
  cout << endl << endl;
                  
  cout << "0 ^ 0 = " << (0 ^ 0) << endl;
  cout << "0 ^ 2 = " << (0 ^ 2) << endl;
  cout << "2 ^ 0 = " << (2 ^ 0) << endl;
  cout << "2 ^ 2 = " << (2 ^ 2) << endl;
  cout << endl << endl;
                  
  cout << "1 ^ 1 = " << (1 ^ 1) << endl;
  cout << "1 ^ 2 = " << (1 ^ 2) << endl;
  cout << "2 ^ 1 = " << (2 ^ 1) << endl;
  cout << "2 ^ 2 = " << (2 ^ 2) << endl;

  return 0;
}
