#include "STLContainerLike.h"

#include <UnitCpp.h>
#include <set>

//=============================================================================
TEST(STLContainerLike, stl)
{
  static_assert(
    STLContainerLike<std::vector<int>>::value,
    "vector should be STLContainerLike."
  );
  static_assert(
    STLContainerLike<std::set<std::string>>::value,
    "vector should be STLContainerLike."
  );
  static_assert(
    STLContainerLike<std::map<int, double>>::value,
    "vector should be STLContainerLike."
  );
  static_assert(
    STLContainerLike<std::vector<int>>::value,
    "vector should be STLContainerLike."
  );
}

//=============================================================================
TEST(STLContainerLike, non_stl)
{
  static_assert(
    !STLContainerLike<int>::value,
    "int isn't an STL container."
  );
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
