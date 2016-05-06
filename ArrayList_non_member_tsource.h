//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator begin(ArrayList<tCONTAINS>& list)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator begin(
  const ArrayList<tCONTAINS>& list
)
{
  return list.begin();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator end(ArrayList<tCONTAINS>& list)
{
  return list.end();
}

//=============================================================================
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator end(
  const ArrayList<tCONTAINS>& list
)
{
  return list.end();
}

//=============================================================================
template <typename tCONTAINS>
bool operator==(
  const ArrayList<tCONTAINS>& lhs,
  const ArrayList<tCONTAINS>& rhs
)
{
  bool ret_val = lhs.size() == rhs.size();
  if (ret_val) {
    auto l = begin(lhs);
    auto r = begin(rhs);
    while (l != end(lhs) && r != end(rhs)) {
      if (!(*l == *r)) {
        ret_val = false;
        break;
      }
      ++l;
      ++r;
    }
  }
  return ret_val;
}

//=============================================================================
template <typename tCONTAINS>
bool operator!=(
  const ArrayList<tCONTAINS>& lhs,
  const ArrayList<tCONTAINS>& rhs
)
{
  return !(lhs == rhs);
}

