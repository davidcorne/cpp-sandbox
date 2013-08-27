//
// 

#include <iostream>
#include <functional>

int main() {
  std::function<int(int)> func1 = [](int i) { return i+4; };
   func2 = [](int i) { return i+4; };
  std::cout << func1(5) << std::endl;
  return 0;
}

