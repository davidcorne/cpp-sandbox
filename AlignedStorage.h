#ifndef AlignedStorage_H
#define AlignedStorage_H

#include <type_traits>

template <typename tTYPE>
using AlignedStorage =
  typename std::aligned_storage<sizeof(tTYPE), std::alignment_of<tTYPE>::value>::type;

#endif
