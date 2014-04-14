//=============================================================================
//
//D Inspired by
// http://gameprogrammingpatterns.com/event-queue.html

#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

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
  friend class utest_RingBuffer;
  static const int MAX_ARRAY = 5;
  int m_head;
  int m_tail;
  T m_array[MAX_ARRAY];
};

//=============================================================================
struct Request {
  int Num;
  string Descriptiton;
};

typedef Ring<Request> RequestRing;

//=============================================================================
class utest_RingBuffer : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_add();
    test_count();
    test_max_size();
  }

private:

  void test_add();
  void test_count();
  void test_max_size();

};

//=============================================================================
void utest_RingBuffer::test_add()
{
  print(DGC_CURRENT_FUNCTION);
  RequestRing ring;
  ring.add({0, "Hey"});
  Request request = ring.update();
  test(request.Num == 0, "Correct Num.");
  test(request.Descriptiton == "Hey", "Correct Descriptiton.");
}

//=============================================================================
void utest_RingBuffer::test_max_size()
{
  print(DGC_CURRENT_FUNCTION);
  test(RequestRing().max_size() == 5, "Wrong max size");
}

//=============================================================================
void utest_RingBuffer::test_count()
{
  print(DGC_CURRENT_FUNCTION);
  RequestRing ring;
  test(ring.size() == 0, "Wrong size");

  ring.add({0, "Hey"});
  test(ring.size() == 1, "Wrong size");

  ring.add({1, "Hey"});
  test(ring.size() == 2, "Wrong size");

  ring.add({2, "Hey"});
  test(ring.size() == 3, "Wrong size");

  ring.add({3, "Hey"});
  test(ring.size() == 4, "Wrong size");

  ring.update();
  ring.update();
  test(ring.size() == 2, "Wrong size");

  ring.add({3, "Hey"});
  ring.add({3, "Hey"});
  test(ring.size() == 4, "Wrong size");
}

//=============================================================================
int main() {
  utest_RingBuffer test;
  test.run_tests();
  return 0;
}
