//=============================================================================
//
// 

#include "LinkedList.h"
#include "LinkedListImpl.C"
#include "utest_LinkedList.C"

//=============================================================================
int main() {
  utest_LinkedList t;
  t.run_tests();
  return 0;
}
