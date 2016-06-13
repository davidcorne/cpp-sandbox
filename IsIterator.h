//=============================================================================
//
// A tag struct to work out if a class is an STL style iterator.

#ifndef IsIterator_H
#define IsIterator_H

#include <type_traits>

//=============================================================================
template <typename tTYPE>
struct IsIterator :
  public std::integral_constant<bool, !std::is_integral<tTYPE>::value>
{
};

#endif
