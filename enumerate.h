//=============================================================================
#ifndef enumerate_H
#define enumerate_H

#include <vector>

//=============================================================================
template <typename CONTAINER>
std::vector<std::pair<int, typename CONTAINER::value_type> > enumerate(
  const CONTAINER& container
)
{
  std::vector<std::pair<int, typename CONTAINER::value_type> > map;
  int i = 0;
  for (auto value: container) {
    map.push_back(std::make_pair(i, value));
    ++i;
  }
  return map;
}
#endif
