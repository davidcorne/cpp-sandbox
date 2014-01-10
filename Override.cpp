//=============================================================================
//
// 

#include <iostream>
#include "gcc_version.h"

using namespace std;

#if GCC_VERSION > 40800
//=============================================================================
class Base {
public:

 // without virtual override does not work.
  virtual void thing();
};

//=============================================================================
class Override : public Base {
public:

  virtual void thing() override;
  
};
#endif

//=============================================================================
int main() {
  return 0;
}
