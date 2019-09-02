//=============================================================================

#include <iostream>

//=============================================================================
class PrivateStuff {

  friend class TestInstance;
  int m_int;
  
};

//=============================================================================
class TestGroup {
public:

  TestGroup();
  
  virtual ~TestGroup();
};

//=============================================================================
class TestInstance : public TestGroup {
public:

  TestInstance();
  virtual ~TestInstance();

  void print_int(const PrivateStuff& p);
};

//=============================================================================
int main()
{
  PrivateStuff private_stuff{};
  TestInstance instance{};
  instance.print_int(private_stuff);
  return 0;
}

//=============================================================================
void TestInstance::print_int(const PrivateStuff& p)
{
  std::cout << p.m_int << std::endl;
}

TestInstance::TestInstance() {}
TestInstance::~TestInstance() {}

TestGroup::TestGroup() {}
TestGroup::~TestGroup() {}

