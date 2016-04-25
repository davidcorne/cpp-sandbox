//=============================================================================
//
// 

#include "Zip.h"

#include <UnitCpp.h>

//=============================================================================
TEST(utest_Zip, usage)
{

  std::vector<int> a = {0, 1, 2, 3, 4, 5};
  std::vector<int> b = {0, 1, 2, 3, 4, 5};
  std::vector<int> result;
  for (const auto& pair : zip(a, b)) {
    result.push_back(pair.first + pair.second);
  }
  
  std::vector<int> expected = {0, 2, 4, 6, 8, 10};
  for (std::size_t i = 0; i < expected.size(); ++i) {
    TEST_EQUAL(result[i], expected[i]);
  }

  // <nnn> // Now try modifying the original sequence
  // <nnn> for (auto& pair : zip(a, b)) {
  // <nnn>   pair.first *= 2;
  // <nnn> }
  // <nnn> for (std::size_t i = 0; i < expected.size(); ++i) {
  // <nnn>   TEST_EQUAL(a[i], expected[i]);
  // <nnn> }
  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
