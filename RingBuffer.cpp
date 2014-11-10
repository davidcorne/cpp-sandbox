//=============================================================================
//
//D Inspired by
// http://gameprogrammingpatterns.com/event-queue.html

#include <assert.h>
#include <iostream>
#include <string>

#include <UnitCpp/Test.h>

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
  std::string Descriptiton;
};

typedef Ring<Request> RequestRing;

//=============================================================================
TEST(RingBuffer, add)
{
  RequestRing ring;
  ring.add({0, "Hey"});
  Request request = ring.update();
  TEST_EQUAL(request.Num, 0, "Correct Num.");
  TEST_EQUAL(request.Descriptiton, "Hey", "Correct Descriptiton.");
}

//=============================================================================
TEST(RingBuffer, max_size)
{
  TEST_EQUAL(RequestRing().max_size(), 5, "Wrong max size");
}

//=============================================================================
TEST(RingBuffer, count)
{
  RequestRing ring;
  TEST_EQUAL(ring.size(), 0, "Wrong size");

  ring.add({0, "Hey"});
  TEST_EQUAL(ring.size(), 1, "Wrong size");

  ring.add({1, "Hey"});
  TEST_EQUAL(ring.size(), 2, "Wrong size");

  ring.add({2, "Hey"});
  TEST_EQUAL(ring.size(), 3, "Wrong size");

  ring.add({3, "Hey"});
  TEST_EQUAL(ring.size(), 4, "Wrong size");

  ring.update();
  ring.update();
  TEST_EQUAL(ring.size(), 2, "Wrong size");

  ring.add({3, "Hey"});
  ring.add({3, "Hey"});
  TEST_EQUAL(ring.size(), 4, "Wrong size");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
