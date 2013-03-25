// from The Programming Antihero here
// http://www.gamasutra.com/view/feature/132500/dirty_coding_tricks.php?page=4

#include <iostream>

using namespace std;

// 2 Mb spare memory
static char spare[1024*1024*2];

int main() {
  cout << sizeof(spare) << endl;
  while (true) {

  }
  return 0;
}
