//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_THREAD_LOCAL_VARIABLES

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

//=============================================================================
class Outputter {
public:
  Outputter();
  ~Outputter();
  
  void out(int i) const;
  
private:
  Outputter(const Outputter&);
  Outputter* operator=(const Outputter&);
  
  mutable std::mutex m_lock;
};

static Outputter OUT;

//=============================================================================
void wait_seconds(int seconds)
{
  for (int i = seconds; i != 0; --i) {
    OUT.out(i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  
}

//=============================================================================
int main() {

  std::vector<std::thread*> thread_pool;
  for (int i = 10; i != 0; --i) {
    auto wait_thread = new std::thread(wait_seconds, i);
    thread_pool.push_back(wait_thread);
  }
  for (auto it = begin(thread_pool); it != end(thread_pool); ++it) {
    (*it)->join();
    delete *it;
  }
  return 0;
}

//=============================================================================
Outputter::Outputter()
{}

//=============================================================================
Outputter::~Outputter()
{}

//=============================================================================
void Outputter::out(int i) const
{
  m_lock.lock();
  std::cout << i << std::endl;  
  m_lock.unlock();
}

#else // CAPABILITY_THREAD_LOCAL_VARIABLES
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_THREAD_LOCAL_VARIABLES)
#endif
