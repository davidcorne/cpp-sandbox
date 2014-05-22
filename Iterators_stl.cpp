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
#include <memory>


//=============================================================================
template<typename T>
class AbsIterator {
public:

  AbsIterator();

  virtual ~AbsIterator();

  virtual std::unique_ptr<AbsIterator<T> > clone() const = 0;
  
  virtual bool operator++() = 0;

  virtual T& operator()() = 0;

  virtual const T& operator()() const = 0;

private:

  AbsIterator(const AbsIterator<T>& iter);
  AbsIterator<T>& operator=(const AbsIterator<T>& iter);
  
};

//=============================================================================
template<typename T>
class Iterator {
public:

  Iterator(std::unique_ptr<AbsIterator<T> > iter);

  ~Iterator();

  Iterator(const Iterator& iter);

  Iterator& operator=(const Iterator& iter);

  bool operator++();

  T& operator()();

  const T& operator()() const;
  
private:

  std::unique_ptr<AbsIterator<T> > m_iter;

};

//=============================================================================
namespace IteratorCreators {

  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container);
  
}

//=============================================================================
int main()
{
  std::vector<int> array;
  array.push_back(0);
  array.push_back(1);
  array.push_back(2);
  array.push_back(3);
  array.push_back(4);
  
  Iterator<int> iter_1 = IteratorCreators::iter(array);
  while (++iter_1) {
    std::cout << iter_1() << std::endl;
  }
  
  Iterator<int> iter_2 = IteratorCreators::iter(array);
  while (++iter_2) {
    iter_2() += 1;
  }
  
  std::cout << std::endl;
  
  Iterator<int> iter_3 = IteratorCreators::iter(array);
  while (++iter_3) {
    std::cout << iter_3() << std::endl;
  }
  
  return 0;
}

//=============================================================================
template <typename T>
AbsIterator<T>::AbsIterator()
{
}

//=============================================================================
template <typename T>
AbsIterator<T>::~AbsIterator()
{
}

//=============================================================================
template <typename T>
Iterator<T>::Iterator(std::unique_ptr<AbsIterator<T> > iter)
  : m_iter(std::move(iter))
{
}

//=============================================================================
template <typename T>
Iterator<T>::~Iterator()
{
}

//=============================================================================
template <typename T>
Iterator<T>::Iterator(const Iterator<T>& iter)
  : m_iter(std::move(iter.m_iter->clone()))
{
}

//=============================================================================
template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iter)
{
  m_iter = iter.m_iter->clone();
  return *this;
}

//=============================================================================
template <typename T>
bool Iterator<T>::operator++()
{
  return m_iter->operator++();
}

//=============================================================================
template <typename T>
T& Iterator<T>::operator()()
{
  return m_iter->operator()();
}

//=============================================================================
template <typename T>
const T& Iterator<T>::operator()() const
{
  return m_iter->operator()();
}

//=============================================================================
template <typename ITER>
class STLIteratorWrapper : public AbsIterator<typename ITER::value_type> {
public:

  typedef typename ITER::value_type CONTAINED;
  
  STLIteratorWrapper(const ITER& begin, const ITER& end);

  virtual ~STLIteratorWrapper();

  virtual std::unique_ptr<AbsIterator<CONTAINED> > clone() const override;
  
  virtual bool operator++() override;

  virtual typename ITER::value_type& operator()() override;

  virtual const CONTAINED& operator()() const override;

private:

  const ITER m_begin;
  const ITER m_end;
  
  ITER m_iter;

};

//=============================================================================
namespace IteratorCreators {
  template <typename CONTAINER>
  Iterator<typename CONTAINER::value_type> iter(CONTAINER& container)
  {
    typedef typename CONTAINER::value_type T;
    AbsIterator<T>* abs_iter =
      new STLIteratorWrapper<typename CONTAINER::iterator>(
        std::begin(container),
        std::end(container)
      );
    std::unique_ptr<AbsIterator<T> > ptr(abs_iter);
    
    Iterator<T> iter(std::move(ptr));
    return iter;
  }
}
//=============================================================================
template <typename ITER>
STLIteratorWrapper<ITER>::STLIteratorWrapper(
  const ITER& begin,
  const ITER& end
)
  : m_begin(begin),
    m_end(end),
    m_iter(end)
{
}

//=============================================================================
template <typename ITER>
STLIteratorWrapper<ITER>::~STLIteratorWrapper()
{
}

//=============================================================================
template <typename ITER>
std::unique_ptr<AbsIterator<typename ITER::value_type> >
  STLIteratorWrapper<ITER>::clone() const
{
  auto stl_iter = new STLIteratorWrapper<ITER>(m_begin, m_end);
  stl_iter->m_iter = m_iter;
  std::unique_ptr<AbsIterator<CONTAINED> > ptr(std::move(stl_iter));
  return std::move(ptr);
}

//=============================================================================
template <typename ITER>
bool STLIteratorWrapper<ITER>::operator++()
{
  if (m_iter == m_end) {
    m_iter = m_begin;
  } else {
    ++m_iter;
  }
  bool ok = m_iter != m_end;
  return ok;
}

//=============================================================================
template <typename ITER>
typename ITER::value_type& STLIteratorWrapper<ITER>::operator()()
{
  return *m_iter;
}

//=============================================================================
template <typename ITER>
const typename ITER::value_type& STLIteratorWrapper<ITER>::operator()() const
{
  return *m_iter;
}
