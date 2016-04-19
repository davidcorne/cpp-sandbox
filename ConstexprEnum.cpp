//=============================================================================
//
// Trying to answer http://stackoverflow.com/q/32793174/1548429

#include "Capabilities.h"
#if CAPABILITY_CONSTEXPR
#include <cstdint>

//=============================================================================
constexpr const std::uint8_t ascii_to_3bit(char c)
{
  return (c & 0x60) - 1;
}

//=============================================================================
enum class Column : std::uint8_t
{
    A = ascii_to_3bit('a'),
    B = ascii_to_3bit('b'),
    C = ascii_to_3bit('c'),
    D = ascii_to_3bit('d'),
    E = ascii_to_3bit('e'),
    F = ascii_to_3bit('f'),
    G = ascii_to_3bit('g'),
    H = ascii_to_3bit('h')
};

//=============================================================================
int main()
{
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR);
#endif
