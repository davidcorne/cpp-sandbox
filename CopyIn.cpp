//=============================================================================
// This is a template copy-in class which uses the curiously recurring template
// pattern.

#include <iostream>

//=============================================================================
template <typename CopyClass>
class CopyIn {
public:

  CopyIn();
  virtual ~CopyIn();
  
  virtual void copy_in(const CopyClass& copy_in) = 0;

};


//=============================================================================
class Point : public CopyIn<Point> {
public:

  Point(double x, double y);
  
  ~Point();

  virtual void copy_in(const Point& other_point) override;

  double x() const;
  
  double y() const;
  
private:

  double m_x;
  double m_y;
};

std::ostream& operator<<(std::ostream& os, const Point& point);

//=============================================================================
int main()
{
  Point a(1, 0);
  Point b(0, 1);
  a.copy_in(b);
  std::cout << "a = " << a << ", b = " << b << std::endl;
  return 0;
}

//----- CopyIn<T>.
template <typename T>
CopyIn<T>::CopyIn() {}

template <typename T>
CopyIn<T>::~CopyIn() {}

//----- Point.

//=============================================================================
Point::Point(double x, double y)
  : m_x(x),
    m_y(y)
{
}

//=============================================================================
Point::~Point()
{
}

//=============================================================================
double Point::x() const
{
  return m_x;
}

//=============================================================================
double Point::y() const
{
  return m_y;
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << "(" << point.x() << ", " << point.y() << ")";
  return os;
}

//=============================================================================
void Point::copy_in(const Point& other_point)
{
  m_x = other_point.x();
  m_y = other_point.y();
}
