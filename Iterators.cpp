//=============================================================================
// Getting from generic STL iterators to iterators you can do this:
//
// Iterator<int> iter = container.iter();
// while (++iter) {
//   iter() += 5;
// }

#include <assert.h>
#include <iostream>
#include <vector>

template<typename T>
class Array;

//=============================================================================
template<typename T>
class Iterator {
public:

  Iterator(Array<T>& array);

  ~Iterator();

  Iterator(const Iterator& iter);

  Iterator& operator=(const Iterator& iter);

  bool operator++();

  T& operator()();

  const T& operator()() const;
  
private:

  bool valid() const;

  Array<T>* m_array;
  int m_pos;
};

//=============================================================================
template<typename T>
class Array {
public:

  Array();

  ~Array();

  void add_item(T i);

  int length() const;
  
  T& operator[](int index);

  const T& operator[](int index) const;

  Iterator<T> iter();

private:

  Array(const Array& array);
  Array& operator=(const Array& array);

  std::vector<T> m_storage;
  
};

  
//=============================================================================
int main()
{
  Array<int> array;
  array.add_item(0);
  array.add_item(1);
  array.add_item(2);
  array.add_item(3);
  array.add_item(4);
  Iterator<int> iter_1 = array.iter();
  while (++iter_1) {
    std::cout << iter_1() << std::endl;
  }
  Iterator<int> iter_2 = array.iter();
  while (++iter_2) {
    iter_2() += 1;
  }
  std::cout << std::endl;
  Iterator<int> iter_3 = array.iter();
  while (++iter_3) {
    std::cout << iter_3() << std::endl;
  }
  return 0;
}

//=============================================================================
template<typename T>
Iterator<T>::Iterator(Array<T>& array)
  : m_array(&array),
    m_pos(-1)
{
}

//=============================================================================
template<typename T>
Iterator<T>::~Iterator()
{
}

//=============================================================================
template<typename T>
Iterator<T>::Iterator(const Iterator<T>& iter)
  : m_array(iter.m_array),
    m_pos(iter.m_pos)
{
}

//=============================================================================
template<typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iter)
{
  m_array = iter.m_array;
  m_pos = iter.m_pos;
  return *this;
}

//=============================================================================
template<typename T>
bool Iterator<T>::operator++()
{
  ++m_pos;
  return valid();
}

//=============================================================================
template<typename T>
T& Iterator<T>::operator()()
{
  assert(valid());
  return (*m_array)[m_pos];
}

//=============================================================================
template<typename T>
const T& Iterator<T>::operator()() const
{
  assert(valid());
  return (*m_array)[m_pos];
}

//=============================================================================
template<typename T>
bool Iterator<T>::valid() const
{
  return m_array && -1 < m_pos && m_pos < m_array->length();
}

//=============================================================================
template<typename T>
Array<T>::Array()
{
}

//=============================================================================
template<typename T>
Array<T>::~Array()
{
}

//=============================================================================
template<typename T>
void Array<T>::add_item(T item)
{
  m_storage.push_back(item);
}

//=============================================================================
template<typename T>
int Array<T>::length() const
{
  return static_cast<int>(m_storage.size());
}

//=============================================================================
template<typename T>
T& Array<T>::operator[](int index)
{
  return m_storage[index];
}

//=============================================================================
template<typename T>
const T& Array<T>::operator[](int index) const
{
  return m_storage[index];
}

//=============================================================================
template<typename T>
Iterator<T> Array<T>::iter()
{
  return Iterator<T>(*this);
}
