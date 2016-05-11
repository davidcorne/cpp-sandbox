//=============================================================================
//
// 

#ifndef CharCode_H
#define CharCode_H

#include <algorithm>
#include <string>

#include <cassert>
#include <cmath>

// <nnn> //=============================================================================
// <nnn> class CharCode {
// <nnn> public:

  
  
// <nnn> private:
  
// <nnn> };

using CharCode = std::string;

int to_int(CharCode code);

CharCode from_int(int i);


//=============================================================================
int to_int(CharCode code)
{
  int result = 0;
  int power = 0;
  for (auto it = code.rbegin(); it != code.rend(); ++it) {
    char c = *it;
    int i = c - 96;
    assert((1 <= i && i <= 27) && "Character should be a-z.");
    // Note: only ascii compatible.
    result += static_cast<int>(i * std::pow(26, power));
    ++power;
  }
  return result;
}

// <nnn> //=============================================================================
// <nnn> CharCode from_int(int i)
// <nnn> {
// <nnn>   CharCode result("");
// <nnn>   while (i > 0) {
// <nnn>     char c = (i % 26) + 96;
// <nnn>     result += c;
// <nnn>     i /= 26;
// <nnn>   }
// <nnn>   std::reverse(begin(result), end(result));
// <nnn>   return result;
// <nnn> }

//=============================================================================
CharCode from_int(int value)
{
  if (value == 0) {
    return CharCode("");
  }
  
  // Shift all values down by 1 since the string representation 'number system'
  // effectively starts from 1 not 0.
  --value;

  // Base case for when the value is in the range 1-26.
  if (value < 26) {
    return CharCode(1, static_cast<char>('a' + value));
  }

  // Recurse to find representation of value / 26.
  CharCode str = from_int(value / 26);

  // Add the character representation of the remainder as the least significant
  // position in the string.
  int remainder = value % 26;
  str += CharCode(1, static_cast<char>('a' + remainder));

  return str;
}

#endif
