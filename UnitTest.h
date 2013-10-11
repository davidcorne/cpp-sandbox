#include <assert.h>
#include <iostream>
#include <string>

//=============================================================================
class UnitTest {

  virtual void run_tests() = 0;

protected:

  void test(bool pass, std::string message) {
    
    if (pass) {
      message = "Pass: " + message;
    } else {
      message = "Fail: " + message;
    }
    std::cout << message << std::endl;
    assert(pass);
  }

  void print(std::string message) {
    std::string banner(
      "======================================="
      "========================================"
    );
    std::cout << "\n"
              << banner <<  "\n"
              << message << "\n"
              << banner << "\n"
              << "\n";
    std::cout.flush();
  }
};
