//=============================================================================
//
// 

#ifndef EnumerationIterator_H
#define EnumerationIterator_H

//=============================================================================
template <typename CONTAINER>
class EnumerationIterator {
public:

  typedef typename CONTAINER::const_iterator iter;
  
  EnumerationIterator(iter begin, iter end, iter current, int pos)
    : m_begin(begin),
      m_end(end),
      m_current(current),
      m_pos(pos)
    {}
  
  bool operator==(const EnumerationIterator<CONTAINER>& other) const
    {
      return m_current == other.m_current;
    }
  
  bool operator!=(const EnumerationIterator<CONTAINER>& other) const
    {
      return !(*this == other);
    }

  void operator++()
    {
      ++m_current;
      ++m_pos;
    }

  std::pair<int, typename CONTAINER::value_type> operator*()
    {
      return std::pair<int, typename CONTAINER::value_type>(m_pos, *m_current);
    }

private:
  const iter m_begin;
  const iter m_end;
  iter m_current;
  int m_pos;
};

#endif
