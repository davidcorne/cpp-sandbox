//=============================================================================
//
// This code is from http://www.cplusplus.com/forum/articles/6046/ but modified
// to not use namespace std.

#define CONSTANT_CONDITIONAL
#include "IgnoreDiagnostics.h"

#include <iostream>
#include <string>
#include <sstream>

//=============================================================================
int main()
{
  std::string input = "";

  // How to get a string/sentence with spaces
  std::cout << "Please enter a valid sentence (with spaces):\n>";
  std::getline(std::cin, input);
  std::cout << "You entered: " << input << std::endl << std::endl;

  // How to get a number.
  int myNumber = 0;

  while (true) {
    std::cout << "Please enter a valid number: ";
    std::getline(std::cin, input);

    // This code converts from string to number safely.
    std::stringstream myStream(input);
    if (myStream >> myNumber) {
      break;
    }
    std::cout << "Invalid number, please try again" << std::endl;
  }
  std::cout << "You entered: " << myNumber << std::endl << std::endl;

  // How to get a single char.
  char myChar  = {0};

  while (true) {
    std::cout << "Please enter 1 char: ";
    std::getline(std::cin, input);

    if (input.length() == 1) {
      myChar = input[0];
      break;
    }

    std::cout << "Invalid character, please try again" << std::endl;
  }
  std::cout << "You entered: " << myChar << std::endl << std::endl;

  std::cout << "All done. And without using the >> operator" << std::endl;

  return 0;
}
