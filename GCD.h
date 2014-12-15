//=============================================================================
// A crazy awesome recursive template greatest common divisor algorithm.

#ifndef GCD_H
#define GCD_H

//=============================================================================
template <int X, int Y>
struct GCD {
  constexpr static const int result = GCD<Y, X % Y>::result;
};

//=============================================================================
template <int X>
struct GCD<X, 0> {
  constexpr static const int result = X;
};

// need to be declared and initialised
// See http://stackoverflow.com/a/16730438/1548429 
template <int X, int Y>
constexpr const int GCD<X, Y>::result;

template <int X>
constexpr const int GCD<X, 0>::result;

#endif
