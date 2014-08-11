#include <iostream>

//=============================================================================
int main()
{
  int size;
  std::cout << "What size array? ";
  std::cin >> size;

  int array[size];
  for (int i = 0; i < size; ++i) {
    array[i] = i + 1;
  }
  std::cout << std::endl;
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << std::endl;
  }
  return 0;
}
