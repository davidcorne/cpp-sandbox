//=============================================================================
//
// From MSM2Cb my C++ course at Uni

#include <iostream>
#include <vector>

//=============================================================================
int main() {

  const int N = 3;
  double I[N][N];
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      I[i][j] = i == j ? 1.0 : 0.0;
    }
  }
  std::cout << "ID:" << std::endl;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cout << " " << I[i][j];
    }
    std::cout << std::endl;
  }
  
  return 0;
}
