//=============================================================================
// This is a fixed size array, to prove you can make an Iterator from non-stl
// classes.

#ifndef DGCArray_H
#define DGCArray_H

#include <cassert>

//=============================================================================
namespace DGC {
  
  //===========================================================================
  template <typename T>
  class Array {
  public:

    typedef T DGC_VALUE_TYPE;
    Array(int size, T value);

    int size() const;

    const T& operator[](int index) const;
    T& operator[](int index);
    
  private:
    T& get(int index);
    
    T* m_data;
    int m_size;
  };

  //===========================================================================
  template <typename T>
  Array<T>::Array(int size, T value)
    : m_data(nullptr),
      m_size(size)
  {
    m_data = new T[m_size];
    for (int i = 0; i < m_size; ++i) {
      m_data[i] = value;
    }
  }

  //===========================================================================
  template <typename T>
  int Array<T>::size() const
  {
    return m_size;
  }

  //===========================================================================
  template <typename T>
  const T& Array<T>::operator[](int index) const
  {
    assert(index < m_size);
    return m_data[index];
  }

  //===========================================================================
  template <typename T>
  T& Array<T>::operator[](int index)
  {
    assert(index < m_size);
    return m_data[index];
  }
}

#endif
