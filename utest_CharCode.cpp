//=============================================================================
//

#include "CharCode.h"

#include <UnitCpp.h>

//=============================================================================
TEST(CharCode, to_int)
{
  std::vector<std::pair<CharCode, int>> tests{
    {"", 0},
    {"a", 1},
    {"b", 2},
    {"c", 3},
    {"d", 4},
    {"e", 5},
    {"f", 6},
    {"g", 7},
    {"h", 8},
    {"i", 9},
    {"j", 10},
    {"k", 11},
    {"l", 12},
    {"m", 13},
    {"n", 14},
    {"o", 15},
    {"p", 16},
    {"q", 17},
    {"r", 18},
    {"s", 19},
    {"t", 20},
    {"u", 21},
    {"v", 22},
    {"w", 23},
    {"x", 24},
    {"y", 25},
    {"z", 26},
    {"aa", 27},
    {"ab", 28},
    {"ac", 29},
    {"ad", 30},
    {"ae", 31},
    {"af", 32},
    {"ag", 33},
    {"ah", 34},
    {"ai", 35},
    {"aj", 36},
    {"ak", 37},
    {"al", 38},
    {"am", 39},
    {"an", 40},
    {"ao", 41},
    {"ap", 42},
    {"aq", 43},
    {"ar", 44},
    {"as", 45},
    {"at", 46},
    {"au", 47},
    {"av", 48},
    {"aw", 49},
    {"ax", 50},
    {"ay", 51},
    {"az", 52},
    {"ba", 53},
    {"aba", 729}, // 26^2 + 2 * 26 + 1 = 729
    {"ca", 79}, // 3 * 26 + 1 = 79
    {"david", 1860590} // 4 * 26^4 + 26^3 + 22 * 26^2 + 9 * 26 + 4 = 1860590
  };
  for (std::pair<CharCode, int> test : tests) {
    std::cout << test.first << ": " << to_int(test.first) << "\n";
    TEST_EQUAL(to_int(test.first), test.second);
  }
}

//=============================================================================
TEST(CharCode, from_int)
{
  std::vector<std::pair<int, CharCode>> tests{
    {0, ""},
    {1, "a"},
    {2, "b"},
    {3, "c"},
    {4, "d"},
    {5, "e"},
    {6, "f"},
    {7, "g"},
    {8, "h"},
    {9, "i"},
    {10, "j"},
    {11, "k"},
    {12, "l"},
    {13, "m"},
    {14, "n"},
    {15, "o"},
    {16, "p"},
    {17, "q"},
    {18, "r"},
    {19, "s"},
    {20, "t"},
    {21, "u"},
    {22, "v"},
    {23, "w"},
    {24, "x"},
    {25, "y"},
    {26, "z"},
    {27, "aa"},
    {28, "ab"},
    {29, "ac"},
    {30, "ad"},
    {1860590, "david"},
  };
  for (std::pair<int, CharCode> test : tests) {
    std::cout << test.first << ": " << from_int(test.first) << "\n";
    TEST_EQUAL(from_int(test.first), test.second);
  }
    
    // <nnn> for (int i = 0; i < (27*27 + 2); ++i) {
    // <nnn>   std::cout << i << ": " << from_int(i) << "\n";
    // <nnn> }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
