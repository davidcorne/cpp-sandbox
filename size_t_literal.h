//=============================================================================
// A user defined literal for size_t values.

#include "Capabilities.h"
#include <limits>
#include <stdexcept>

#if defined(CAPABILITY_CONSTEXPR) && defined(CAPABILITY_USER_DEFINED_LITERALS)
constexpr std::size_t operator"" _st(unsigned long long n)
{
  // Apparently can't static_assert :(
  return n <= std::numeric_limits<std::size_t>::max() ?
    n :
    throw std::overflow_error("User defined literal value too large.");
}

#endif
