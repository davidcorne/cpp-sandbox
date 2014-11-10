//=============================================================================
//
// This is a hard one to do in one file, a summery of this idom is at
// http://c2.com/cgi/wiki?PimplIdiom
//

#include <iostream>
#include <memory>

#include <UnitCpp/Test.h>

//=============================================================================
class Impl {
public:

  Impl();
  ~Impl();

  int file_handle() const;
  
private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m_pimpl;
};

//=============================================================================
TEST(PIMPL, handle)
{
  Impl impl;
  TEST_EQUAL(impl.file_handle(), 77, "Wrong file handle.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
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
