//=============================================================================
//

// <nnn> 
#ifndef STLContainerLike_H
#define STLContainerLike_H


template <class tCONTAINER> char stl_container_like(
  typename tCONTAINER::value_type*
);

template <class tCONTAINER> short stl_container_like(...);


// This template class has a constexpr 'value' which is true for stl containers.
template <class tCONTAINER>
struct STLContainerLike {
  static const bool value =
    sizeof(stl_container_like<tCONTAINER>(0)) == sizeof(char);
};

static_assert(
  sizeof(char) != sizeof(short),
  "char shouldn't be the size of short."
);

#endif
