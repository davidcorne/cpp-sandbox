//
// 

#include <iostream>
#include <memory>

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
    if (!m_area.get()) {
      std::cout << "Calculating" << std::endl;
      std::shared_ptr<int> ptr(new int);
      m_area = ptr;
      *m_area = m_x * m_y;
    } else {
      std::cout << "Calculated" << std::endl;
    }      
    return *m_area;
  }

private:
  int m_x;
  int m_y;
  mutable std::shared_ptr<int> m_area;
};

int main() {
  Rect f(4,5);
  std::cout << f.area() << std::endl;
  std::cout << f.area() << std::endl;
  return 0;
}
