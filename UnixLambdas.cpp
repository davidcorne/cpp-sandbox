//=============================================================================
// The idea was inspired by this blog post:
// http://pfultz2.com/blog/2014/09/05/pipable-functions/
// 
// However, I took it in a completely different direction.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>


//=============================================================================
namespace unix {

typedef std::string String;
  
//=============================================================================
class Options {
public:

  Options();
  // Default constructor.

  template <typename T>
  Options(T options_string);
  // Constructor with argument for String constructor.
  
private:

  String m_options;
};


//=============================================================================
class Operation {
public:

  virtual String operator()(String in) const = 0;
  
};

//=============================================================================
String operator|(String source, const Operation& function);

//=============================================================================
template <typename tOUT>
void split(String string, String::value_type delimiter, tOUT ouput_iterator);

//=============================================================================
template <typename tIN>
String join(tIN begin, tIN end, String::value_type delimiter);

} // namespace unix

           
//=============================================================================
class grep : public unix::Operation {
public:
  
  grep(unix::String re);
  
  virtual unix::String operator()(unix::String in) const override;

private:

  unix::String m_re;
};

//=============================================================================
class wc : public unix::Operation {
public:

  wc(unix::Options options=unix::Options());

  virtual unix::String operator()(unix::String in) const override;
};

//=============================================================================
class echo : public unix::Operation {
public:

  echo();

  virtual unix::String operator()(unix::String in) const override;
  
};
  
//=============================================================================
class sort : public unix::Operation {
public:

  sort();

  virtual unix::String operator()(unix::String in) const override;
  
};
  
//=============================================================================
int main() {
  unix::String result = echo()("hi\nthere\nbeautiful!") | sort();
  std::cout << result << std::endl;
}

//=============================================================================
grep::grep(unix::String re)
  : m_re(re)
{
}

//=============================================================================
unix::String grep::operator()(unix::String in) const
{
  return in;
}

//=============================================================================
wc::wc(unix::Options options)
{
}

//=============================================================================
unix::String wc::operator()(unix::String in) const
{
  std::stringstream ss;
  ss << in.length();
  return ss.str();
}

//=============================================================================
echo::echo()
{
}

//=============================================================================
unix::String echo::operator()(unix::String out) const
{
  return out;
}

//=============================================================================
sort::sort()
{
}

//=============================================================================
unix::String sort::operator()(unix::String out) const
{
  std::vector<unix::String> after;
  unix::split(out, '\n', back_inserter(after));
  std::sort(begin(after), end(after));
  return unix::join(begin(after), end(after), '\n');
}

//=============================================================================
namespace unix {
  
//=============================================================================
Options::Options()
  : m_options("")
{
}

//=============================================================================
template <typename T>
Options::Options(T options_string)
  : m_options(options_string)
{
}

//=============================================================================
String operator|(String source, const Operation& function)
{
  return function(source);
}

//=============================================================================
template <typename tOUT>
void split(String string, String::value_type delimiter, tOUT ouput_iterator)
{
  std::vector<std::pair<String::size_type, String::size_type> > pairs;
  String::size_type previous = 0;
  for (String::size_type i = 0; i < string.length(); ++i) {
    if (string[i] == delimiter) {
      pairs.push_back(std::make_pair(previous, i));
      previous = i + 1;
    }
  }
  pairs.push_back(std::make_pair(previous, string.length() + 1));
  // e.g. if string: "hello\nyou" delimiter: '\n'
  //         pairs: {0, 5}, {6, 9}

  for (auto it = begin(pairs); it != end(pairs); ++it) {
    String token(string, it->first, it->second - it->first);
    *ouput_iterator = token;
    ++ouput_iterator;
  }
}

//=============================================================================
template <typename tIN>
String join(tIN begin, tIN end, String::value_type delimiter)
{
  String out;
  for (auto it = begin; it != end; ++it) {
    out += *it;
    out += delimiter;
  }
  return out.substr(0, out.size() - 1);
}

} // namespace unix

