//=============================================================================

#ifndef AbsIterator_H
#define AbsIterator_H

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
template <typename T>
AbsIterator<T>::AbsIterator()
{
}

//=============================================================================
template <typename T>
AbsIterator<T>::~AbsIterator()
{
}

#endif
