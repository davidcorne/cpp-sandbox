//=============================================================================
//
//D Inspired by
// http://gameprogrammingpatterns.com/event-queue.html?utm_source=Game+Programming+Patterns&utm_campaign=cbce6efb6e-Observer&utm_medium=email&utm_term=0_0c27329244-cbce6efb6e-38213733

#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

//=============================================================================
struct Request {
  int Num;
  string Descriptiton;
};

//=============================================================================
class RequestRing {
public:

  RequestRing()
    : m_head(0),
      m_tail(0)
    {}

  void add(Request r) {
    assert((m_tail + 1) % MAX_ARRAY != m_head);
    m_array[m_tail].Num = r.Num;
    m_array[m_tail].Descriptiton = r.Descriptiton;
    m_tail = (m_tail + 1) % MAX_ARRAY;
  }
    
  Request update() {
    // basically a pop
    Request request = m_array[m_head];
    m_head = (m_head + 1) % MAX_ARRAY;
    return request;
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
  
  ~RequestRing(){}
      
private:
  friend class utest_RingBuffer;
  static const int MAX_ARRAY = 5;
  int m_head;
  int m_tail;
  Request m_array[MAX_ARRAY];
};

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
