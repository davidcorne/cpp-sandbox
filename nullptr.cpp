//
// 

#include <iostream>
#include <memory>

using namespace std;

class Rect {
public:

  Rect(int i, int j)
    : m_x(i),
      m_y(j),
      m_area(nullptr)
    {
    }

  int area() const {
    // if it's already set return it, otherwise work it out
    if (m_area.get() == nullptr) {
      cout << "Calculating" << endl;
      shared_ptr<int> ptr(new int);
      m_area = ptr;
      *m_area = m_x * m_y;
    } else {
      cout << "Calculated" << endl;
    }      
    return *m_area;
  }

private:
  int m_x;
  int m_y;
  mutable shared_ptr<int> m_area;
};

int main() {
  Rect f(4,5);
  cout << f.area() << endl;
  cout << f.area() << endl;
  return 0;
}
