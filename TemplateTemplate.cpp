//=============================================================================
//
// 

#include <UnitCpp.h>

#include <deque>
#include <vector>

template <
  template <typename, typename> class tCONTAINER,
  typename tVALUE,
  typename tALLOCATOR=std::allocator<tVALUE>
>
tCONTAINER<tVALUE, tALLOCATOR> one_to_ten()
{
  tCONTAINER<tVALUE, tALLOCATOR> container = {
    tVALUE{0},
    tVALUE{1},
    tVALUE{2},
    tVALUE{3},
    tVALUE{4},
    tVALUE{5},
    tVALUE{6},
    tVALUE{7},
    tVALUE{8},
    tVALUE{9},
    tVALUE{10}
  };
  return container;
}


//=============================================================================
TEST(TemplateTemplate, vector)
{
  std::vector<int> vector = one_to_ten<std::vector, int>();
  int current = 0;
  for (int i : vector) {
    TEST_EQUAL(current, i);
    ++current;
  }
}


//=============================================================================
TEST(TemplateTemplate, deque)
{
  std::deque<int> deque = one_to_ten<std::deque, int>();
  int current = 0;
  for (int i : deque) {
    TEST_EQUAL(current, i);
    ++current;
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
