//=============================================================================
//
// 

#include <UnitCpp.h>
#include <string>

//=============================================================================
class Address {
public:

  Address();

  Address& set_line_1(std::string line_1);
  std::string line_1() const;
  
  Address& set_line_2(std::string line_2);
  std::string line_2() const;

  Address& set_post_code(std::string post_code);
  std::string post_code() const;

  ~Address();

private:

  Address(const Address&);
  Address& operator=(const Address&);
  // Prohibited copy.
  
  std::string m_line_1;
  std::string m_line_2;
  std::string m_post_code;
};

//=============================================================================
Address::Address()
  : m_line_1(""),
    m_line_2(""),
    m_post_code("")
{
}

//=============================================================================
Address::~Address()
{
}

//=============================================================================
Address& Address::set_line_1(std::string line_1)
{
  m_line_1 = line_1;
  return *this;
}

//=============================================================================
std::string Address::line_1() const
{
  return m_line_1;
}

//=============================================================================
Address& Address::set_line_2(std::string line_2)
{
  m_line_2 = line_2;
  return *this;
}

//=============================================================================
std::string Address::line_2() const
{
  return m_line_2;
}

//=============================================================================
Address& Address::set_post_code(std::string post_code)
{
  m_post_code = post_code;
  return *this;
}

//=============================================================================
std::string Address::post_code() const
{
  return m_post_code;
}

//=============================================================================
TEST(NamedParameterIdiom, a)
{
  Address example;
  example.set_line_1("22").set_line_2("Edingburgh Road.").set_post_code("Ed9");
  TEST_EQUAL(example.line_1(), "22");
  TEST_EQUAL(example.line_2(), "Edingburgh Road.");
  TEST_EQUAL(example.post_code(), "Ed9");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
