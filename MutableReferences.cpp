//=============================================================================
//
// 

#include <UnitCpp.h>

class NonConstClass;

//=============================================================================
class MutableReference {
public:

  MutableReference(NonConstClass& r);

  int calculate() const;
  // Note: const.

  MutableReference(const MutableReference&) = delete;
  MutableReference& operator=(const MutableReference&) = delete;
private:
  NonConstClass& m_r;
};

//=============================================================================
class NonConstClass {
public:

  void change_value();
  // Note: non-const.

private:
  int m_int;
};

//=============================================================================
MutableReference::MutableReference(NonConstClass& r)
  : m_r(r)
{
}

//=============================================================================
int MutableReference::calculate() const
{
  m_r.change_value();
  return 5;
}

//=============================================================================
void NonConstClass::change_value()
{
  m_int = 5;
}

//=============================================================================
TEST(MutableReferences, )
{
  NonConstClass c;
  MutableReference r(c);
  r.calculate();
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
