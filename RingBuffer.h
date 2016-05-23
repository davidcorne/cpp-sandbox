#ifndef RingBuffer_H
#define RingBuffer_H

#include <cassert>

//=============================================================================
template <typename T>
class Ring {
public:

  Ring()
    : m_head(0),
      m_tail(0)
    {}

  void add(T t) {
    assert((m_tail + 1) % MAX_ARRAY != m_head);
    m_array[m_tail] = t;
    m_tail = (m_tail + 1) % MAX_ARRAY;
  }
    
  T update() {
    // basically a pop
    T t = m_array[m_head];
    m_head = (m_head + 1) % MAX_ARRAY;
    return t;
  }

  int size() const {
      int count = 0;
      if (m_head == m_tail) {
        count = 0;
      } else if (m_head > m_tail) {
        count = MAX_ARRAY - (m_head - m_tail);
      } else {
        count = m_tail - m_head;
      }
      assert(count <= MAX_ARRAY);
      return count;
    }

  int max_size() const {
    return MAX_ARRAY;
  }
  
  ~Ring(){}
      
private:
  static const int MAX_ARRAY = 5;
  int m_head;
  int m_tail;
  T m_array[MAX_ARRAY];
};

#endif
