#include <iostream>

using namespace std;

int main()
{
  int size;
  cout << "What size array? ";
  cin >> size;

  int arr_2[size];
  for (int i = 0; i < size; ++i) {
    arr_2[i] = i + 1;
  }
  cout << endl;
  for (int i = 0; i < size; ++i) {
    cout << arr_2[i] << endl;
  }
  return 0;
}
