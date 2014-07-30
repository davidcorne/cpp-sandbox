//=============================================================================
//
// This is a hard one to do in one file, a summery of this idom is at
// http://c2.com/cgi/wiki?PimplIdiom
//

#include <iostream>
#include <memory>

#include "UnitTest.h"

using namespace std;


//=============================================================================
class Impl {
public:

  Impl();
  ~Impl();

  int file_handle() const;
  
private:
  struct Pimpl;
  unique_ptr<Pimpl> m_pimpl;
};

//=============================================================================
class utest_PIMPL : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_handle();
  }

private:

  void test_handle();

};

//=============================================================================
void utest_PIMPL::test_handle()
{
  print(DGC_CURRENT_FUNCTION);
  Impl impl;
  test(impl.file_handle() == 77, "Wrong file handle.");

}

//=============================================================================
int main() {
  utest_PIMPL test;
  test.run_tests();
  return 0;
}

//=============================================================================
// Source file
// <nnn>  #include <some prohibited file> e.g. <windows.h>
struct Impl::Pimpl {
  int handle;
};

Impl::Impl()
  : m_pimpl(new Pimpl)
{
  m_pimpl->handle = 77;
}

int Impl::file_handle() const
{
  return m_pimpl->handle;
}

Impl::~Impl()
{
}
