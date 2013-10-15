//=============================================================================
//
// From MSM2Cb my C++ course at Uni

#include <iostream>
#include <vector>

using namespace std;

//=============================================================================
int main() {

  int N = 3;
  double I[N][N];
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      I[i][j] = i == j ? 1.0 : 0.0;
    }
  }
  cout << "ID:" << endl;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << " " << I[i][j];
    }
    cout << endl;
  }
  
  return 0;
}
