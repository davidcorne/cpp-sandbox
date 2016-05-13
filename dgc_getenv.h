//=============================================================================
#ifndef dgc_getenv_H
#define dgc_getenv_H

#include <cstdlib>

#include <string>

namespace DGC {
  
//=============================================================================
std::pair<bool, std::string> getenv(std::string variable)
{
  char* buffer = 0;
  std::pair<bool, std::string> ret_val{false, ""};
#ifdef _MSC_VER  
  std::size_t size = 0;
  if (_dupenv_s(&buffer, &size, variable.c_str()) == 0) {
    ret_val.first = true;
    // Takes a copy
    ret_val.second = std::string(buffer);
    free(buffer);
  }
#else
  buffer = std::getenv(variable.c_str());
  if (buffer) {
    ret_val.first = true;
    ret_val.second = std::string(buffer);
  }
#endif
  return ret_val;
}
  
}

#endif
