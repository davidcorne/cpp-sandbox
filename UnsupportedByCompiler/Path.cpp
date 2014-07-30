//=============================================================================
//
#include <iostream>

#ifdef _MSC_VER
#if _MSC_VER >= 1700

#include <filesystem>

//=============================================================================
int main()
{
  
  return 0;
}

#else
int main()
{
  std::cout << "Compiler not supported." << std::endl;
  return 0;
}
#endif
#endif

