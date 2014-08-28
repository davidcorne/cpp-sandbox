//=============================================================================
//
//D Inspired by
//D http://code.activestate.com/recipes/66531-singleton-we-dont-need-no-stinkin-singleton-the-bo/
//

#include <iostream>

//=============================================================================
class Borg {
public:

  Borg();

  void set_i(int i);
  int i() const;
  
private:
  static int s_i;
};

int Borg::s_i(0);

//=============================================================================
Borg::Borg()
{
}

//=============================================================================
int main() {
  Borg b_1;
  b_1.set_i(5);
  Borg b_2;
  std::cout << b_2.i() << std::endl;
  b_1.set_i(-5);
  
  std::cout << b_1.i() << " " << b_2.i() << std::endl;
  
  return 0;
}

//=============================================================================
void Borg::set_i(int i)
{
  s_i = i;
}

//=============================================================================
int Borg::i() const
{
  return s_i;
}
