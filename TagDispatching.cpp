#include <iostream>

template <int>
struct ThreadSafety {
};

typedef ThreadSafety<0> thread_safe;
typedef ThreadSafety<1> non_thread_safe;

//=============================================================================
class ThreadSafeData {
public:
  typedef thread_safe ThreadSafety;
};

//=============================================================================
class NonThreadSafeData {
public:
  typedef non_thread_safe ThreadSafety;
  
};

//=============================================================================
template <typename T>
void work_dispatch(T, thread_safe)
{
  std::cout << "thread_safe" << std::endl;
}

//=============================================================================
template <typename T>
void work_dispatch(T, non_thread_safe)
{
  std::cout << "non_thread_safe" << std::endl;
}

//=============================================================================
template <typename T>
void work(T t)
{
  typename T::ThreadSafety thread_safety;
  work_dispatch(t, thread_safety);
}

//=============================================================================
int main () {
  ThreadSafeData thread_safe;
  NonThreadSafeData non_thread_safe;
  work(thread_safe);
  work(non_thread_safe);

  return 0;
}
