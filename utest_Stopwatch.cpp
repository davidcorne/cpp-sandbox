#include "Stopwatch.h"
#include "Stopwatch.h"

#include <UnitCpp.h>

//=============================================================================
TEST(Stopwatch, time)
{
  Stopwatch watch;
  watch.start();
  // do something
  std::vector<int> v(1000, 7);
  for (int& i : v) {
    ++i;
  }
  std::chrono::duration<double> duration = watch.stop();
  std::cout << duration.count() << "\n";
  TEST_TRUE(0 <= duration.count());
  TEST_TRUE(0 <= watch.duration().count());
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
