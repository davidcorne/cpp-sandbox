//=============================================================================
// Some common, testable string operations.

#ifndef StringOperations_H
#define StringOperations_H

#include <string>
#include <vector>

//=============================================================================
template <typename tOUT, typename tSTRING=std::string>
void split(
  const tSTRING& string,
  typename tSTRING::value_type delimiter,
  tOUT ouput_iterator
);

//=============================================================================
template <typename tIN, typename tSTRING=std::string>
tSTRING join(tIN begin, tIN end, typename tSTRING::value_type delimiter);

//----- Source.

//=============================================================================
template <typename tOUT, typename tSTRING>
void split(
  const tSTRING& string,
  typename tSTRING::value_type delimiter,
  tOUT ouput_iterator
)
{
  std::vector<
    std::pair<typename tSTRING::size_type, typename tSTRING::size_type>
  > pairs;
  typename tSTRING::size_type previous = 0;
  for (typename tSTRING::size_type i = 0; i < string.length(); ++i) {
    if (string[i] == delimiter) {
      pairs.push_back(std::make_pair(previous, i));
      previous = i + 1;
    }
  }
  pairs.push_back(std::make_pair(previous, string.length() + 1));
  // e.g. if string: "hello\nyou" delimiter: '\n'
  //         pairs: {0, 5}, {6, 9}

  for (auto it = begin(pairs); it != end(pairs); ++it) {
    tSTRING token(string, it->first, it->second - it->first);
    *ouput_iterator = token;
    ++ouput_iterator;
  }
}

//=============================================================================
template <typename tIN, typename tSTRING>
tSTRING join(tIN begin, tIN end, typename tSTRING::value_type delimiter)
{
  tSTRING out;
  for (auto it = begin; it != end; ++it) {
    out += *it;
    out += delimiter;
  }
  return out.substr(0, out.size() - 1);
}

#endif
