//=============================================================================
//
// 

#ifndef StringBuilder_H
#define StringBuilder_H

#include <string>
#include <vector>

//=============================================================================
class StringBuilder {
public:

  StringBuilder() = default;

  // Note: has a tFIRST so that this doesn't define a default constructor with
  // 0 arguments.
  template <typename tFIRST, typename... tARGS>
  StringBuilder(tFIRST first, tARGS...);
  
  StringBuilder& append(std::string s);

  StringBuilder& operator+=(std::string s);

  StringBuilder& operator<<(std::string s);

  void clear();

  std::string build() const;
  
private:

  using size_type = std::string::size_type;

  std::vector<std::string> m_strings;
};

#include <cassert>

//=============================================================================
template <typename tFIRST, typename... tARGS>
StringBuilder::StringBuilder(tFIRST first, tARGS... arguments)
  : m_strings(first, arguments...)
{

}
//=============================================================================
StringBuilder& StringBuilder::append(std::string s)
{
  m_strings.push_back(s);
  return *this;
}

//=============================================================================
StringBuilder& StringBuilder::operator<<(std::string s)
{
  return append(s);
}

//=============================================================================
StringBuilder& StringBuilder::operator+=(std::string s)
{
  return append(s);
}

//=============================================================================
void StringBuilder::clear()
{
  m_strings.clear();
}

//=============================================================================
std::string StringBuilder::build() const
{
  size_type n = 0;
  for (const std::string& s : m_strings) {
    n += s.size();
  }
  std::string result(n, char{});
  size_type i = 0;
  for (const std::string& s : m_strings) {
    size_type length = s.length();
    result.replace(i, length, s);
    i += length;
  }
  assert(i == n && "Should have transfered all of the characters.");
  return result;
}


#endif
