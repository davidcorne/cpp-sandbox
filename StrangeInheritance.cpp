//=============================================================================
// This is (modified version of) a strange example of the C++ hiding rules.
// Taken from: http://blogs.msdn.com/b/vcblog/archive/2011/01/28/10121387.aspx

#include <iostream>
#include <sstream>
#include <memory>

#include <UnitCpp/Test.h>

//=============================================================================
class Foo {
public:

  virtual void do_stuff() = 0;

};
  
//=============================================================================
class Bar : public Foo {
public:

  virtual void do_stuff(int a) = 0;
  // C++ standard 3.3.10 point 3, says:
  //   In a member function definition, the declaration of a name at block
  //   scope hides the declaration of a member of the class with the same name;
  //   see 3.3.7. The declaration of a member in a derived class (Clause 10)
  //   hides the declaration of a member of a base class of the same name; see
  //   10.2.
  // So this hides Foo::do_stuff() even though there have different signatures.

  // Need to add Foo::do_stuff() to this scope.
  using Foo::do_stuff;
};
  
//=============================================================================
class Baz : public Bar {
public:

  Baz(std::ostream& os)
    : m_os(os)
    {
    }
  
  void do_stuff(int a) override {
    m_os << "Baz::do_stuff(" << a << ")" << std::endl;
  }
  
  void do_stuff() override {
    m_os << "Baz::do_stuff()" << std::endl;
  }

private:

  std::ostream& m_os;
};

//=============================================================================
TEST(StrangeInheritance, test)
{
  std::stringstream ss;
  std::unique_ptr<Bar> bar(new Baz(ss));
  bar->do_stuff();
  TEST_EQUAL(ss.str(), "Baz::do_stuff()\n");
  ss.str("");
  bar->do_stuff(5);
  TEST_EQUAL(ss.str(), "Baz::do_stuff(5)\n");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

