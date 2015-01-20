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

#include "Capabilities.h"
#ifdef CAPABILITY_DEFAULT_FUNCTION_TEMPLATE_ARGS
#include "StringOperations.h"

//=============================================================================
namespace nix {

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

} // namespace nix

           
//=============================================================================
class grep : public nix::Operation {
public:
  
  grep(nix::String re);
  
  virtual nix::String operator()(nix::String in) const override;

private:

  nix::String m_re;
};

//=============================================================================
class wc : public nix::Operation {
public:

  wc(nix::Options options=nix::Options());

  virtual nix::String operator()(nix::String in) const override;
};

//=============================================================================
class echo : public nix::Operation {
public:

  echo();

  virtual nix::String operator()(nix::String in) const override;
  
};
  
//=============================================================================
class sort : public nix::Operation {
public:

  sort();

  virtual nix::String operator()(nix::String in) const override;
  
};
  
//=============================================================================
int main() {
  nix::String result = echo()("hi\nthere\nbeautiful!") | sort();
  std::cout << result << std::endl;
}

//=============================================================================
grep::grep(nix::String re)
  : m_re(re)
{
}

//=============================================================================
nix::String grep::operator()(nix::String in) const
{
  return in;
}

//=============================================================================
wc::wc(nix::Options options)
{
}

//=============================================================================
nix::String wc::operator()(nix::String in) const
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
nix::String echo::operator()(nix::String out) const
{
  return out;
}

//=============================================================================
sort::sort()
{
}

//=============================================================================
nix::String sort::operator()(nix::String out) const
{
  std::vector<nix::String> after;
  split(out, '\n', back_inserter(after));
  std::sort(begin(after), end(after));
  return join(begin(after), end(after), '\n');
}

//=============================================================================
namespace nix {
  
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


} // namespace nix

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_DEFAULT_FUNCTION_TEMPLATE_ARGS)
#endif
