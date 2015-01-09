//=============================================================================

#ifndef MetaDivides_H
#define MetaDivides_H

#include "Capabilities.h"

#if !CAPABILITY_CONSTEXPR
#error "You need constexpr for this header."
#endif

//=============================================================================
template <unsigned int X, unsigned int Y>
struct Divides {
  constexpr static const bool result = Y % X == 0;
};

template <unsigned int X, unsigned int Y>
constexpr const bool Divides<X, Y>::result;

#endif
