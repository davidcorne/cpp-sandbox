//=============================================================================
// This shows how to redirect std::cout to a string stream.

#include <cstdio>

#include <iostream>
#include <sstream>

#include <UnitCpp.h>

//=============================================================================
void output(std::string message)
{
  std::cout << message << "\n";
}

//=============================================================================
TEST(RedirectStdOut, cout)
{
  std::stringstream ss;
  // Save old buffer
  auto cout_buffer = std::cout.rdbuf();
  // Redirect std::cout to ss.
  std::cout.rdbuf(ss.rdbuf());

  output("Hi there.");
  TEST_EQUAL(ss.str(), "Hi there.\n");
  ss.str("");

  // Direct std::cout back to it's original buffer.
  std::cout.rdbuf(cout_buffer);

}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

