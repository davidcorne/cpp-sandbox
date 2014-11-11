//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_ATOMICS
#include <atomic>
#include <thread>
#include <vector>

#include <UnitCpp/Test.h>

//=============================================================================
class Counter {
public:

  Counter(int i)
    : m_count(0)
    {}
  
  void operator++() {
    int c = count();
    ++c;
    m_count = c;
  }

  int count() const {
    return m_count;//.load();
  }
  
private:

  Counter(const Counter&) = delete;
  Counter& operator=(const Counter&) = delete;
  
  int m_count;
};

//=============================================================================
TEST(Atomics, counter)
{
  Counter counter(0);
  std::vector<std::thread> thread_pool;
  std::function<void(int)> add = [&counter](int number){
    for (int i = 0; i < number; ++i) {
      ++counter;
    }
  };
  for (int i = 0; i < 20; ++i) {
    thread_pool.push_back(std::thread(add, 20 - i));
  }
  for (std::thread& thread: thread_pool) {
    thread.join();
  }
  int count = counter.count();
  TEST_EQUAL(
    count,
    210,
    "Should have been incremented 210 times, not ",
    count,
    " times."
  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN
#endif
