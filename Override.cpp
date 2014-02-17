//=============================================================================
//
// 

#include <iostream>
#include "compiler_guards.h"

using namespace std;

#if CPP_ELEVEN_SUPPORTED
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
