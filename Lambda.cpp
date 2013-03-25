#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector <int> v;
  for (int n = 0; n < 20; n++) {
    v.push_back(n);
  }

  cout << "There are "
       << count_if( v.begin(), v.end(), bind2nd( less <int> (), 10 ) )
       << " ints less than 10"
       << endl;
  return 0;
}
