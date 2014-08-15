//=============================================================================

#ifndef to_string_H
#define to_string_H

#include <string>
#include <sstream>

//=============================================================================
template <typename T>
std::string to_string(const T& t);

//----- Source

//=============================================================================
template <typename T>
std::string to_string(const T& t)
{
  std::ostringstream ss;
  ss << t;
  return ss.str();
}

#endif
