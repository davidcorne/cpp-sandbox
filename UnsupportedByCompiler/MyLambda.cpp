#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::function;

//=============================================================================
double eval(function<double(double)> f, double x)
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
  cout << eval(return_one, 5) << endl;
  cout << eval([] (double x){return x*x;} , 5) << endl;
  return 0;
}
