//=============================================================================
//
// 

#ifndef Stopwatch_H
#define Stopwatch_H

#include <chrono>

//=============================================================================
class Stopwatch {
public:

  Stopwatch();
  
  void start();

  std::chrono::duration<double> stop();

  std::chrono::duration<double> duration() const;

private:

  using timer = std::chrono::high_resolution_clock;
  using time_point = timer::time_point;
  time_point m_start;
  time_point m_stop;
};


//=============================================================================
Stopwatch::Stopwatch()
  : m_start(time_point::min()),
    m_stop(time_point::max())
{

}

//=============================================================================
void Stopwatch::start()
{
  m_start = timer::now();
}

//=============================================================================
std::chrono::duration<double> Stopwatch::stop()
{
  m_stop = timer::now();
  return duration();
}

//=============================================================================
std::chrono::duration<double> Stopwatch::duration() const
{
  return m_stop - m_start;
}

#endif
