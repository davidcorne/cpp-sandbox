// I think
// http://stackoverflow.com/questions/1096341/function-pointers-casting-in-c
// is wrong.

#include <cctype>
#include <iostream>
#include <string>

//=============================================================================
void convert(char (*character_function)(char))
{
  std::string str("hello ThIs IS 78998");
  for (unsigned int i = 0; i < str.length(); ++i) {
    str[i] = character_function(str[i]);
  }
  std::cout << str << std::endl;
}

//=============================================================================
void horrific(void* input)
{
  convert(reinterpret_cast<char (*)(char)>(input));
}

//=============================================================================
int main()
{
  int (*to_upper_func)(int) = std::toupper;

  horrific(reinterpret_cast<void*>(to_upper_func));

  char (*character_function)(char) =
    reinterpret_cast<char (*)(char)>(to_upper_func);

  convert(character_function);
  return 0;
}
