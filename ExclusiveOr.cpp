// testing what bitwise (I think) Xor does

#include <iostream>

void print_xor(int a, int b)
{
  std::cout << a << " ^ " << b << " = " << (a ^ b) << std::endl;
}

void print_xor_combinations(int a, int b)
{
  print_xor(a, a);
  print_xor(a, b);
  print_xor(b, a);
  print_xor(b, b);
  std::cout << std::endl << std::endl;
}

int main() {
  print_xor_combinations(0, 1);
  print_xor_combinations(0, 4);
  print_xor_combinations(0, -1);
  print_xor_combinations(0, 2);

  return 0;
}
