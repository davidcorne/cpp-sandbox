//=============================================================================
//
// 

#ifndef Zip_H
#define Zip_H

#include <utility>

//=============================================================================
template <typename tVALUE, typename tITERATOR>
class ZipIterator {
public:

  using value_type = std::pair<const tVALUE&, const tVALUE&>;

  ZipIterator(tITERATOR a, tITERATOR b)
    : m_a(a),
      m_b(b)
    {
    }
  
  ZipIterator(const ZipIterator<tVALUE, tITERATOR>& other) = default;
  ZipIterator<tVALUE, tITERATOR>& operator=(
    const ZipIterator<tVALUE, tITERATOR>& other
  ) = default;

  value_type operator*() {
    return std::make_pair(*m_a, *m_b);
  }

  void operator++() {
    ++m_a;
    ++m_b;
  }

private:

  template <typename tVALUE_2, typename tITERATOR_2>
  friend bool operator==(
    const ZipIterator<tVALUE_2, tITERATOR_2>& a,
    const ZipIterator<tVALUE_2, tITERATOR_2>& b
  );

  tITERATOR m_a;
  tITERATOR m_b;
};

template <typename tVALUE, typename tITERATOR>
bool operator==(
  const ZipIterator<tVALUE, tITERATOR>& a,
  const ZipIterator<tVALUE, tITERATOR>& b
) {
  return (a.m_a == b.m_a) && (a.m_b == b.m_b);
}
template <typename tVALUE, typename tITERATOR>
bool operator!=(
  const ZipIterator<tVALUE, tITERATOR>& a,
  const ZipIterator<tVALUE, tITERATOR>& b
) {
  return !(a == b);
}

//=============================================================================
template <typename tVALUE, typename tCONTAINER>
class Zip {
public:

  Zip(const tCONTAINER& a, const tCONTAINER& b)
    : m_a(a),
      m_b(b)
    {
    }
  
  ZipIterator<tVALUE, typename tCONTAINER::const_iterator> begin() {
    using std::begin;
    return ZipIterator<tVALUE, typename tCONTAINER::const_iterator>(
      begin(m_a),
      begin(m_b)
    );
  }
  ZipIterator<tVALUE, typename tCONTAINER::const_iterator> end() {
    using std::end;
    return ZipIterator<tVALUE, typename tCONTAINER::const_iterator>(
      end(m_a),
      end(m_b)
    );
  }
  
private:
  tCONTAINER m_a;
  tCONTAINER m_b;
};

//=============================================================================
template <typename tCONTAINER>
Zip<typename tCONTAINER::value_type, tCONTAINER> zip(
  const tCONTAINER& a,
  const tCONTAINER& b
) {
  return Zip<typename tCONTAINER::value_type, tCONTAINER>(a, b);
}

#endif
