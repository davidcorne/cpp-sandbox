//=============================================================================
#include <iostream>

//=============================================================================
template <typename U>
class FunctionBag {
public:

  template <typename V>
  static U halve(V v)
    {
      // conversion must exist.
      U u = v;
      return u / 2;
    }
private:

  FunctionBag();
  ~FunctionBag();

};

//=============================================================================
int main()
{
  // this won't compile.
  // std::cout << FunctionBag::halve(7) << std::endl;
  std::cout << FunctionBag<double>::halve(7) << std::endl;
}
