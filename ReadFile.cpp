//=============================================================================
//
// Read a whole file into a string.

#include <iostream>
#include <fstream>
#include <string>

//=============================================================================
int main() {
  std::string whole_file;
  std::ifstream infile;
  infile.open("ReadFile.cpp");
  while(!infile.eof()) {
    std::string line("");
    std::getline(infile, line);
    whole_file += line;
    whole_file += "\n";
    
  }
  infile.close();
  std::cout << whole_file << std::endl;
  return 0;
}
