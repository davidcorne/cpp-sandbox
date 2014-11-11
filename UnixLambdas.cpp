//=============================================================================
// The idea was inspired by this blog post:
// http://pfultz2.com/blog/2014/09/05/pipable-functions/

#include "Capabilities.h"

#if CAPABILITY_GENERIC_LAMBDAS

#include <iostream>
#include <string>


//=============================================================================
template <class F>
struct pipe_closure : F
{
    template<class... Xs>
    pipe_closure(Xs&&... xs) : F(std::forward<Xs>(xs)...)
    {}
};

//=============================================================================
template <class T, class F>
decltype(auto) operator|(T&& x, const pipe_closure<F>& p)
{
    return p(std::forward<T>(x));
}

// <nnn> template <typename F>
// <nnn> decltype(auto) operator|(std::string s, const pipe_closure<F>& pipe)
// <nnn> {
// <nnn>   return pipe(s);
// <nnn> }

//=============================================================================
struct grep_f {
  template <class T>
  auto operator()(T x) const {
    return [x](T y){return y;};
  }
};

const pipe_closure<grep_f> grep = {};

//=============================================================================
int main() {
  std::string result = std::string("hi\nthere") | grep("hi");
  std::cout << result << std::endl;
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
