// Using a #include to get some data into the program.
//
// Inspired by
// http://mhesham.wordpress.com/2013/04/25/unusual-c-use-of-include/

#include <iostream>

struct Person
{
  const char* Name;
  unsigned Age;
  unsigned Height;
  char Gender;

  void print() const {
    std::cout
      << Name
      << " "
      << Age
      << " "
      << Height
      << " "
      << Gender
      << std::endl;
  }
};

Person PersonsTable[] = {
  #include "UnusualInclude.txt"
};

int main()
{
  for (unsigned int i = 0; i < (sizeof(PersonsTable) / sizeof(Person)); ++i) {
    Person &person = PersonsTable[i];
    person.print();
  }
  
  return 0;
}

