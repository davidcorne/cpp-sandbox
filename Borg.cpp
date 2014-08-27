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
  
private:
  static void fill_state(Borg* b);

  int m_i;
};

//=============================================================================
Borg::Borg()
{
  Borg::fill_state(this);
}

//=============================================================================
void Borg::fill_state(Borg*)
{
  
}

//=============================================================================
int main() {
  Borg b;
  return 0;
}
