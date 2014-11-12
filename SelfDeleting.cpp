//=============================================================================
//
//D Deletes it's own executable
//

#include <iostream>
#include <stdio.h>
#include <string>

//=============================================================================
int main(int, char* arguments[])
// main function
{
  std::string file_name(arguments[0]);
  file_name += + "/SelfDeleting.exe";
  if (remove(file_name.c_str()) == 0) {
    std::cout << "Somehow I've deleted myself." << std::endl;
  } else {
    std::cerr << "I've not deleted myself, OUTRAGE!!!!" << std::endl;
  }
  return 0;
}
