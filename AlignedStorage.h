#ifndef AlignedStorage_H
#define AlignedStorage_H

#include "AlignOf.h"

#include <type_traits>

template <typename tTYPE>
using AlignedStorage =
  typename std::aligned_storage<sizeof(tTYPE), DGC_ALIGNOF(tTYPE)>::type;

#endif
