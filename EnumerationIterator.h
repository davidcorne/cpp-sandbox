//=============================================================================
//
// 

#ifndef EnumerationIterator_H
#define EnumerationIterator_H

//=============================================================================
template <typename CONTAINER>
class EnumerationIterator {
public:

  typedef typename CONTAINER::const_iterator const_iterator;
  typedef typename CONTAINER::value_type value_type;

  EnumerationIterator(
    const_iterator begin,
    const_iterator end,
    const_iterator current,
    int pos
  );
  
  void operator++();

  std::pair<int, typename CONTAINER::value_type > operator*();

private:
  template <typename U>
  friend bool operator==(
    const EnumerationIterator<U>& first,
    const EnumerationIterator<U>& other
  );

  template <typename U>
  friend bool operator!=(
    const EnumerationIterator<U>& first,
    const EnumerationIterator<U>& other
  );

  const const_iterator m_begin;
  const const_iterator m_end;
  const_iterator m_current;
  int m_pos;
};

template <typename CONTAINER>
bool operator!=(
  const EnumerationIterator<CONTAINER>& first,
  const EnumerationIterator<CONTAINER>& second
);

template <typename CONTAINER>
bool operator==(
  const EnumerationIterator<CONTAINER>& first,
  const EnumerationIterator<CONTAINER>& second
);

//----- Source

//=============================================================================
template <typename CONTAINER>
EnumerationIterator<CONTAINER>::EnumerationIterator(
  const_iterator begin,
  const_iterator end,
  const_iterator current,
  int pos
)
  : m_begin(begin),
    m_end(end),
    m_current(current),
    m_pos(pos)
{}

//=============================================================================
template <typename CONTAINER>
void EnumerationIterator<CONTAINER>::operator++()
{
  ++m_current;
  ++m_pos;
}

//=============================================================================
template <typename CONTAINER>
std::pair<int, typename CONTAINER::value_type> EnumerationIterator<CONTAINER>::operator*()
{
  return std::pair<int, value_type>(m_pos, *m_current);
}

//=============================================================================
template <typename CONTAINER>
bool operator!=(
  const EnumerationIterator<CONTAINER>& first,
  const EnumerationIterator<CONTAINER>& second
)
{
  return !(first == second);
}

//=============================================================================
template <typename CONTAINER>
bool operator==(
  const EnumerationIterator<CONTAINER>& first,
  const EnumerationIterator<CONTAINER>& second
)
{
  return first.m_current == second.m_current;
}

#endif
