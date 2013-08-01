//
//

#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::string string;
  std::ifstream infile;
  infile.open("ReadFile.cpp");
  while(!infile.eof()) {
    std::getline(infile, string);
    std::cout << string << std::endl;
  }
  infile.close();
  return 0;
}
