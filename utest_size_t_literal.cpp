//=============================================================================
//
// 

#include "Capabilities.h"
#if defined(CAPABILITY_CONSTEXPR) && defined(CAPABILITY_USER_DEFINED_LITERALS)

#include <UnitCpp.h>

#include "size_t_literal.h"

//=============================================================================
TEST(size_t_literal, construction)
{
  auto s = 15_st;
  static_assert(
    std::is_same<decltype(s), std::size_t>::value,
    "*_st should be a size_t."
  );
}

//=============================================================================
TEST(size_t_literal, large)
{
  auto large = 18446744073709551615_st;
  TEST_EQUAL(large, std::numeric_limits<std::size_t>::max());
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_USER_DEFINED_LITERALS)
#endif

