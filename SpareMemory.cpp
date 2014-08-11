// from The Programming Antihero here
// http://www.gamasutra.com/view/feature/132500/dirty_coding_tricks.php?page=4
//
// Something called the programming antihero (if you haven't read that article
// I can't recommend it enough!). In this there was a game programmer who
// reserved 2Mb of memory to lose later when memory was tight. I was testing
// to see how this worked by reserving some memory and checking memory usage.
// It is had to see the exact memory usage from this sort of thing due to
// differences in types of memory (i.e. private bytes/working set...) but it
// certainly took some memory.

#include <iostream>

// 2 Mb spare memory
static char spare[1024*1024*2];

int main() {
  std::cout << sizeof(spare) << std::endl;
  while (true) {

  }
  return 0;
}
