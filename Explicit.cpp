#include <iostream>

using namespace std;

class IntType {
public:

  explicit IntType(int i) 
    : m_i(i)
    {}

  int out() const
    {
      return m_i;
    }

private:
  int m_i;
};

void print(IntType i)
{
  cout << i.out() << endl;
}  
  
//=============================================================================
int main() {
  IntType i(5);
  print(i);
  // <nnn>  won't compile
  // <nnn> print(12);
  return 0;
}
