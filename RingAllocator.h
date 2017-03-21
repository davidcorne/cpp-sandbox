//=============================================================================
//
// 

#ifndef RingAllocator_H
#define RingAllocator_H

#include <array>
#include <bitset>

#include <iostream>

#include <cstdlib>
#include <cassert>

#include "AlignedStorage.h"

//=============================================================================
template <typename T, std::size_t Capacity = 128>
class RingAllocator {
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
    typedef RingAllocator<U, Capacity> other;
  };

  struct OutOfMemory {};
  
  struct MemoryLeak {};
  
  RingAllocator();
  
  RingAllocator(const RingAllocator<T, Capacity>& other);

  template<typename U> 
  RingAllocator(const RingAllocator<U, Capacity>& other);

  ~RingAllocator();
  
  T* allocate(std::size_t n);

  void deallocate(T* p, std::size_t n);

  void reset() {s_usage.reset();}
  
  //----- Testing function

  const std::bitset<Capacity>& usage() const { return s_usage;}
  
private:

  T* allocate(std::size_t start, std::size_t end);
  
  static std::array<AlignedStorage<T>, Capacity> s_storage;
  static std::bitset<Capacity> s_usage;
  static std::size_t s_instances;
};

//=============================================================================
template <typename T, std::size_t Capacity>
std::array<AlignedStorage<T>, Capacity> RingAllocator<T, Capacity>::s_storage;

//=============================================================================
template <typename T, std::size_t Capacity>
std::bitset<Capacity> RingAllocator<T, Capacity>::s_usage;

//=============================================================================
template <typename T, std::size_t Capacity>
std::size_t RingAllocator<T, Capacity>::s_instances = 0;

//=============================================================================
template <typename T, int Capacity>
bool operator==(const RingAllocator<T, Capacity> a, const RingAllocator<T, Capacity> b)
{
  return &a == &b;
}

//=============================================================================
template <typename T, int Capacity>
bool operator!=(const RingAllocator<T, Capacity> a, const RingAllocator<T, Capacity> b)
{
  return !(a == b);
}

//=============================================================================
template <typename T, std::size_t Capacity>
RingAllocator<T, Capacity>::RingAllocator()
{
  ++s_instances;
}

//=============================================================================
template <typename T, std::size_t Capacity>
RingAllocator<T, Capacity>::RingAllocator(const RingAllocator<T, Capacity>&)
{
  ++s_instances;
}

//=============================================================================
template <typename T, std::size_t Capacity>
RingAllocator<T, Capacity>::~RingAllocator()
{
  --s_instances;
  if (!s_instances && s_usage.any()) throw MemoryLeak{};
}

//=============================================================================
template <typename T, std::size_t Capacity>
template<typename U> 
RingAllocator<T, Capacity>::RingAllocator(
  const RingAllocator<U, Capacity>& other
)
{
}

//=============================================================================
template <typename T, std::size_t Capacity>
T* RingAllocator<T, Capacity>::allocate(std::size_t n)
{
  std::size_t start = 0;
  std::size_t end = 0;
  for (std::size_t i = 0; i < Capacity; ++i) {
    end = i;
    if ((end - start) == n) {
      // we have found a block of n contiguous memory!
      return allocate(start, end);
    }
    if (s_usage.test(i)) {
      // if it's used, move the start to the next one
      start = i + 1;
    }
  }
  throw OutOfMemory{};
  
}

//=============================================================================
template <typename T, std::size_t Capacity>
T* RingAllocator<T, Capacity>::allocate(std::size_t start, std::size_t end)
{
  assert(!s_usage.test(start) && "Start shouldn't be true.");
  // Mark as used
  for (std::size_t i = start; i < end; ++i) {
    s_usage.set(i, true);
  }

  // Return the area as a pointer
  AlignedStorage<T>* start_ptr = &(s_storage[0]) + start;
  return reinterpret_cast<T*>(start_ptr);
}

template <typename T, std::size_t Capacity>
void RingAllocator<T, Capacity>::deallocate(T* pointer, std::size_t n)
{
  std::size_t start =
    reinterpret_cast<AlignedStorage<T>*>(pointer) - &(s_storage[0]);

  for (std::size_t i = 0; i < n; ++i) {
    s_usage.set(start + i, false);
  }
}
#endif
