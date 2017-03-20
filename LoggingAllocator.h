//=============================================================================
//
// 

#ifndef LoggingAllocator_H
#define LoggingAllocator_H

#include <iostream>
#include <cassert>
#include <cstdlib>

#define CONSTANT_CONDITIONAL 1
#include "IgnoreDiagnostics.h"

//=============================================================================
template <typename T, bool LogAllocation=true, bool LogDeallocation=true>
class LoggingAllocator {
public:

  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  template<class U>
  struct rebind {
    typedef LoggingAllocator<U, LogAllocation, LogDeallocation> other;
  };
  
  LoggingAllocator();
  
  LoggingAllocator(std::ostream* os);
  
  LoggingAllocator(const LoggingAllocator<T, LogAllocation, LogDeallocation>& other) = default;

  template<typename U> 
  LoggingAllocator(const LoggingAllocator<U, LogAllocation, LogDeallocation>& other);

  ~LoggingAllocator() = default;
  
  T* allocate(std::size_t n);

  void deallocate(T* p, std::size_t n);
  
private:

  std::ostream* m_os;
  
};

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
bool operator==(const LoggingAllocator<T, LogAllocation, LogDeallocation> a, const LoggingAllocator<T, LogAllocation, LogDeallocation> b)
{
  return &a == &b;
}

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
bool operator!=(const LoggingAllocator<T, LogAllocation, LogDeallocation> a, const LoggingAllocator<T, LogAllocation, LogDeallocation> b)
{
  return !(a == b);
}

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
LoggingAllocator<T, LogAllocation, LogDeallocation>::LoggingAllocator()
  : m_os(&std::cout)
{

}

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
LoggingAllocator<T, LogAllocation, LogDeallocation>::LoggingAllocator(std::ostream* os)
  : m_os(os)
{
  assert(m_os && "os should not be null.");
}
  
//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
template<typename U> 
LoggingAllocator<T, LogAllocation, LogDeallocation>::LoggingAllocator(const LoggingAllocator<U, LogAllocation, LogDeallocation>& other)
  : m_os(other.m_os)
{
 
}

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
T* LoggingAllocator<T, LogAllocation, LogDeallocation>::allocate(std::size_t n)
{
  if (LogAllocation) {
    (*m_os) << "Allocated " << n << " bytes.\n";
  }
  void* t = ::operator new(n * sizeof (T));
  return reinterpret_cast<T*>(t);
}

//=============================================================================
template <typename T, bool LogAllocation, bool LogDeallocation>
void LoggingAllocator<T, LogAllocation, LogDeallocation>::deallocate(
  T* pointer,
  std::size_t n
)
{
  ::operator delete(pointer);
  if (LogDeallocation) {
    (*m_os) << "Deallocated " << n << " bytes.\n";
  }
}

#endif
