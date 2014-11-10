//=============================================================================
//
// Testing inferring the namespace of a function by it's argument(s). This
// is know as argument dependent lookup.
//

#include <iostream>

//=============================================================================
namespace coi {

//=============================================================================
class Iter {
public:

  explicit Iter(int value);

  ~Iter();

  int value() const;
  
private:

  int m_value;
};

//=============================================================================
Iter add(Iter a, Iter b);
}

//=============================================================================
int main()
{
  coi::Iter a(5);
  coi::Iter b(7);
  coi::Iter result = add(a, b);
  std::cout << result.value() << std::endl;
  return 0;
}

//----- coi::Iter

//=============================================================================
coi::Iter::Iter(int value)
  : m_value(value)
{
}

//=============================================================================
coi::Iter::~Iter()
{
}

//=============================================================================
int coi::Iter::value() const
{
  return m_value;
}

//=============================================================================
coi::Iter coi::add(coi::Iter a, coi::Iter b)
{
  return coi::Iter(a.value() + b.value());
}
