// testing what bitwise (I think) Xor does

#include <iostream>

using namespace std;

void print_xor(int a, int b)
{
  cout << a << " ^ " << b << " = " << (a ^ b) << endl;
}

void print_xor_combinations(int a, int b)
{
  print_xor(a, a);
  print_xor(a, b);
  print_xor(b, a);
  print_xor(b, b);
  cout << endl << endl;
}

int main() {
  print_xor_combinations(0, 1);
  print_xor_combinations(0, 4);
  print_xor_combinations(0, -1);
  print_xor_combinations(0, 2);

  return 0;
}
