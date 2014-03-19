//=============================================================================
//
//D Some playing around with C# style enums

#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class Enumerator {
public:

  Enumerator(string name)
    : m_name(name)
    {}

private:

  string m_name;
};

//=============================================================================
class ReferenceEnumeration {
public:

  ReferenceEnumeration(vector<Enumerator> values)
    : m_values(values)
    {}
  
  vector<Enumerator> values() const
    {
      return m_values;
    }
  
private:
  vector<Enumerator> m_values;
};

//=============================================================================
class Enumeration {
public:

  Enumeration(
    const ReferenceEnumeration& reference,
    vector<Enumerator> applicable
  )
    : m_reference_enumeration(reference)
    {}

  
private:
  const ReferenceEnumeration& m_reference_enumeration;
};


//=============================================================================
class utest_Enumerations : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_();
  }

private:

  void test_();

};

//=============================================================================
void utest_Enumerations::test_()
{
  print(DGC_CURRENT_FUNCTION);

}

//=============================================================================
int main() {
  utest_Enumerations test;
  test.run_tests();
  return 0;
}
