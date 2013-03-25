//to see if dividing by zero compiles

int main()
// main function
{
  int zero = 0;
  // no warning
  double infinity = 1 / zero;

  const int const_zero = 0;
  // warning
  infinity = 1 / const_zero;

  // warning
  infinity = 1 / 0;
return 0;
}
