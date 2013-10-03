#include <iostream>
#include <assert.h>

//=============================================================================
class UnitTest {

protected:

  void test(bool pass, const char* message) {
    if (pass) {
      std::cout << "Pass: " << message << std::endl;
    } else {
      std::cout << "Fail: " << message << std::endl;
      assert(pass);
    }
  }

};
