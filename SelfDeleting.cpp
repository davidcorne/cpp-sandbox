//=============================================================================
//
//D Deletes it's own executable
//

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

//=============================================================================
int main(int num_arguments, char* arguments[])
// main function
{
  string file_name(arguments[0]);
  file_name += + "/SelfDeleting.exe";
  if (remove(file_name.c_str()) == 0) {
    cout << "Somehow I've deleted myself." << endl;
  } else {
    cerr << "I've not deleted myself, OUTRAGE!!!!" << endl;
  }
  return 0;
}
