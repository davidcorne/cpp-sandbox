//=============================================================================

#include <iostream>
#include <string>

#include "MemoryCount.h"

//=============================================================================
class Test {
public:

  Test(std::string name);

  std::string name() const;
  
private:

  std::string m_name;
};


//=============================================================================
Test::Test(std::string name)
  : m_name(name)
{
}

//=============================================================================
std::string Test::name() const
{
  return m_name;
}

//=============================================================================
int main()
{
  std::cout << "Memory: " << MEMORY_USED << std::endl;
  Test* test = new Test("Hello there");
  std::cout << "Memory: " << MEMORY_USED << std::endl;
  std::cout << test->name() << std::endl;
  delete test;
  std::cout << "Memory: " << MEMORY_USED << std::endl;
}

