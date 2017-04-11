//=============================================================================
//
// 

#include <cstdlib>
#include "AlignedStorage.h"

//=============================================================================
template <typename tTYPE>
class Optional {
public:

  struct BadOptionalAccess {};
  
  Optional();

  Optional(const tTYPE& instance);

  ~Optional();
  
  explicit operator bool() const;

  tTYPE& value();
  const tTYPE& value() const;
  
private:

  bool m_defined;
  AlignedStorage<tTYPE> m_storage;
};

//=============================================================================
template <typename tTYPE>
Optional<tTYPE>::Optional()
  : m_defined(false)
{

}

//=============================================================================
template <typename tTYPE>
Optional<tTYPE>::Optional(const tTYPE& type)
  : m_defined(true)
{
  new(&m_storage) tTYPE(type);
}

//=============================================================================
template <typename tTYPE>
Optional<tTYPE>::~Optional()
{
  if (m_defined) {
    value().~tTYPE();
  }
}

//=============================================================================
template <typename tTYPE>
Optional<tTYPE>::operator bool() const
{
  return m_defined;
}

//=============================================================================
template <typename tTYPE>
tTYPE& Optional<tTYPE>::value()
{
  if (!m_defined) throw BadOptionalAccess{};
  return reinterpret_cast<tTYPE&>(m_storage);
}

//=============================================================================
template <typename tTYPE>
const tTYPE& Optional<tTYPE>::value() const
{
  if (!m_defined) throw BadOptionalAccess{};
  return reinterpret_cast<tTYPE&>(m_storage);
}
