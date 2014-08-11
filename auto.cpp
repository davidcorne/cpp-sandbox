#include <iostream>

int main() {
  auto i = 0; // an integer
  auto message = "hey guys"; // a const char*
  auto pi = 3.14159265359; // a float or a double?
  std::cout
    << "Some auto variables: "
    << i
    << ", "
    << message
    << ", "
    << pi
    << std::endl;
  return 0;
}
