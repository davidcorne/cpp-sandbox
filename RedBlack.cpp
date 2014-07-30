//=============================================================================
//=============================================================================
//
// My attempt at an implementation of a red black tree
// see http://en.wikipedia.org/wiki/Red%E2%80%93black_tree

#include "UnitTest.h"

//=============================================================================
class RedBlackTree {
public:

private:
};

//=============================================================================
class utest_RedBlack : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_();
  }

private:

  void test_();

};

//=============================================================================
void utest_RedBlack::test_()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
int main() {
  utest_RedBlack test;
  test.run_tests();
  return 0;
}
