#include <functional>
#include <iostream>

//=============================================================================
double eval(std::function<double(double)> f, double x)
//
//D
//
{
  return f(x);
}

//=============================================================================
double return_one(double x)
//
//D
//
{
  return 1.0;
}

//=============================================================================
int main()
//
//D
//
{
  std::cout << eval(return_one, 5) << std::endl;
  std::cout << eval([] (double x){return x*x;} , 5) << std::endl;
  return 0;
}
