//=============================================================================

#include <iostream>

//=============================================================================
class ConstClass {
public:

  ConstClass()
    : m_num(5)
    {
    }
  
  void non_const_method() {
    m_num += 10;
    std::cout << m_num << std::endl;
  }
private:

  int m_num;

};

//=============================================================================
int main()
//
//D 
//
{
  // dosn't work
  // const ConstClass* const_ptr = new ConstClass();
  ConstClass* const_ptr = new ConstClass();
  const_ptr->non_const_method();
  return 0;
}
