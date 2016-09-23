#include <cstdlib>
#include <iostream>
#include <string>

#include "LoggingAllocator.h"

//=============================================================================
int main()
{
  for (size_t i = 0; i < 50; ++i) {
    std::cout << (i < 10 ? " " : "")
      << i
      << ": "
      << std::basic_string<char, std::char_traits<char>, LoggingAllocator<char, true, false>>(i, '=')
      << std::endl;
  }
  return 0;
}
