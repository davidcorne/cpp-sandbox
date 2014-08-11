//=============================================================================
//
// 

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "UnitTest.h"

//=============================================================================
std::vector<std::string> split(std::string in, char delimiter=' ')
{
  std::vector<std::string> out;
  std::stringstream string_stream(in);
  std::string item;
  while (getline(string_stream, item, delimiter)) {
    out.push_back(item);
  }
  return out;
}

//=============================================================================
class utest_Split : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_space_split();
    test_other_delimiters();
  }

private:

  void test_space_split();
  void test_other_delimiters();

};

//=============================================================================
void utest_Split::test_other_delimiters()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<std::string> out(split("Name,Address,Phone Number", ','));
  test(out.size() == 3, "Wrong size for out.");
  test(out[0] == "Name", "Wrong element 0 in out.");
  test(out[1] == "Address", "Wrong element 1 in out.");
  test(out[2] == "Phone Number", "Wrong element 2 in out.");
  
}

//=============================================================================
void utest_Split::test_space_split()
{
  print(DGC_CURRENT_FUNCTION);
  std::vector<std::string> out(split("This is a sentence."));
  test(out.size() == 4, "Wrong size for out.");
  test(out[0] == "This", "Wrong element 0 in out.");
  test(out[1] == "is", "Wrong element 1 in out.");
  test(out[2] == "a", "Wrong element 2 in out.");
  test(out[3] == "sentence.", "Wrong element 3 in out.");

}

//=============================================================================
int main() {
  utest_Split test;
  test.run_tests();
  return 0;
}
