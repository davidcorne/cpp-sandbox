//=============================================================================
//
// 

#include <iostream>

#include "UnitTest.h"
#include "STLIteratorWrapper.h"

#include <vector>

using namespace std;

//=============================================================================
class utest_STLIteratorWrapper : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_vector_iteration();
    test_empty();
  }

private:

  void test_vector_iteration();
  void test_empty();

};

//=============================================================================
void utest_STLIteratorWrapper::test_vector_iteration()
{
  print(DGC_CURRENT_FUNCTION);
  vector<int> container = {0, 1, 2, 3, 4, 5};
  STLIteratorWrapper<vector<int>::iterator> iter(
    begin(container),
    end(container)
  );
  test(iter.m_iter == end(container), "Should start on an invalid iterator.");
  test(++iter, "++ should give true.");
  test(iter.m_iter == begin(container), "Should be at the beginning.");

  test(iter() == 0, "Wrong element");
  test(++iter, "++ should give true.");

  test(iter() == 1, "Wrong element");
  test(++iter, "++ should give true.");

  test(iter() == 2, "Wrong element");
  test(++iter, "++ should give true.");

  test(iter() == 3, "Wrong element");
  test(++iter, "++ should give true.");

  test(iter() == 4, "Wrong element");
  test(++iter, "++ should give true.");

  test(iter() == 5, "Wrong element");
  test(!(++iter), "++ should give false.");

}

//=============================================================================
void utest_STLIteratorWrapper::test_empty()
{
  print(DGC_CURRENT_FUNCTION);
  vector<int> container;
  STLIteratorWrapper<vector<int>::iterator> iter(
    begin(container),
    end(container)
  );
  test(!(++iter), "Should start false.");
}

//=============================================================================
int main() {
  utest_STLIteratorWrapper test;
  test.run_tests();
  return 0;
}
