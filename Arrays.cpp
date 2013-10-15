#include <iostream>

using namespace std;

//=============================================================================
int main()
{
  int size;
  cout << "What size array? ";
  cin >> size;

  int array[size];
  for (int i = 0; i < size; ++i) {
    array[i] = i + 1;
  }
  cout << endl;
  for (int i = 0; i < size; ++i) {
    cout << array[i] << endl;
  }
  return 0;
}
