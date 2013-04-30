// Using a #include to get some data into the program.
// 

#include <iostream>

using namespace std;

struct Person
{
  const char* Name;
  unsigned Age;
  unsigned Height;
  char Gender;

  void print() const {
    cout << Name << " " << Age << " " << Height << " " << Gender << endl;
  }
};

Person PersonsTable[] = {
    #include "UnusualInclude.txt"
};

int main()
{
  for (int i = 0; i < (sizeof(PersonsTable) / sizeof(Person)); ++i) {
    Person &person = PersonsTable[i];
    person.print();
  }
  
  return 0;
}

