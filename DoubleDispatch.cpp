//=============================================================================
//
// Inspired by item 31 in Scott Meyers "More Effective C++".

#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

//=============================================================================
struct GameObject {

  GameObject();

  virtual ~GameObject() = 0;
};

//=============================================================================
class Asteroid : public GameObject {
public:
};

//=============================================================================
class SpaceShip : public GameObject {
public:
};

//=============================================================================
class MilitarySpaceShip : public SpaceShip {
public:
};

//=============================================================================
class utest_DoubleDispatch : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_();
  }

private:

  void test_();

};

//=============================================================================
void utest_DoubleDispatch::test_()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
int main() {
  utest_DoubleDispatch test;
  test.run_tests();
  return 0;
}
