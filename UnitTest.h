#include <assert.h>
#include <iostream>
#include <string>

// Stolen from BOOST current_function.hpp
namespace implementation_detail {
inline void __current_function_helper()
{

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) || defined(__DMC__)

# define DGC_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define DGC_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define DGC_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define DGC_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define DGC_CURRENT_FUNCTION __func__

#else

# define DGC_CURRENT_FUNCTION "(unknown)"

#endif

}
}

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
