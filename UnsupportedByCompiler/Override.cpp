//=============================================================================
//
// 

#include <iostream>

using namespace std;

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

//=============================================================================
int main() {
  return 0;
}
