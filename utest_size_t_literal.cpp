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
  TEST_EQUAL(s, std::size_t{15});
}

//=============================================================================
TEST(size_t_literal, large)
{
  static_assert(
    std::numeric_limits<std::size_t>::max() < 18446744073709551615u,
    ""
  );
  TEST_THROWS([](){18446744073709551615_st;}, std::overflow_error);
}


//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_USER_DEFINED_LITERALS)
#endif

