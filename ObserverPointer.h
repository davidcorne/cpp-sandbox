//=============================================================================
// This is a class to emulate the behaviour of std::observer_ptr<T>
// see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3840.pdf

#ifndef ObserverPointer_H
#define ObserverPointer_H

#include <cstddef>

//=============================================================================
template <typename T>
class ObserverPtr {
public:
  
  // Default constructor.
  ObserverPtr();

  // Explicit constructor.
  explicit ObserverPtr(T* pointer);

  // Implicit nullptr constructor.
  ObserverPtr(std::nullptr_t ptr);

  // Is the pointer valid?
  operator bool() const;

  // Dereference operator.
  // Precondition: bool()
  T& operator*() const;

  // Pointer calling operator.
  // Precondition: bool()
  T* operator->() const;

  // Get the pointer.
  T* get() const;

  // Conversion operator, if T is convertable to U, the ObserverPtr<T> is
  // convertable to ObserverPtr<U>.
  template <typename U>
  operator ObserverPtr<U>() const;
  
private:

  T* m_pointer;
};

// Equality operator for ObserverPtr.
template <typename T>
bool operator==(const ObserverPtr<T>& a, const ObserverPtr<T>& b);

// Inequality operator for ObserverPtr.
template <typename T>
bool operator!=(const ObserverPtr<T>& a, const ObserverPtr<T>& b);

//----- Source

#include <cassert>

//=============================================================================
// Default constructor.
template <typename T>
ObserverPtr<T>::ObserverPtr()
  : m_pointer(nullptr)
{
}

//=============================================================================
// Explicit constructor.
template <typename T>
ObserverPtr<T>::ObserverPtr(T* pointer)
  : m_pointer(pointer)
{
}

//=============================================================================
// Implicit nullptr constructor.
template <typename T>
ObserverPtr<T>::ObserverPtr(std::nullptr_t ptr)
  : m_pointer(ptr)
{
}

//=============================================================================
// Is the pointer valid?
template <typename T>
ObserverPtr<T>::operator bool() const
{
  return m_pointer ? true : false;
}

//=============================================================================
// Dereference operator.
// Precondition: bool()
template <typename T>
T& ObserverPtr<T>::operator*() const
{
  return *m_pointer;
}

//=============================================================================
// Pointer calling operator.
// Precondition: bool()
template <typename T>
T* ObserverPtr<T>::operator->() const
{
  return m_pointer;
}

//=============================================================================
// Get the pointer.
template <typename T>
T* ObserverPtr<T>::get() const
{
  return m_pointer;
}

//=============================================================================
// Conversion operator, if T is convertable to U, the ObserverPtr<T> is
// convertable to ObserverPtr<U>.
template <typename T>
template <typename U>
ObserverPtr<T>::operator ObserverPtr<U>() const
{
  return ObserverPtr<U>(m_pointer);
}

//=============================================================================
// Equality operator for ObserverPtr.
template <typename T>
bool operator==(const ObserverPtr<T>& a, const ObserverPtr<T>& b)
{
  bool result = !(a || b);
  if (a && b) {
    result = a.get() == b.get();
  }
  return result;
}

//=============================================================================
// Inequality operator for ObserverPtr.
template <typename T>
bool operator!=(const ObserverPtr<T>& a, const ObserverPtr<T>& b)
{
  return !(a == b);
}

#endif
