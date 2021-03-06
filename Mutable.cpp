//=============================================================================

#include <cassert>
#include <iostream>
#include <cmath>

#include <UnitCpp.h>

//=============================================================================
struct Point {
  Point(double new_x, double new_y) {
    x = new_x;
    y = new_y;
  }

  double x;
  double y;
};

//=============================================================================
template <typename T>
class Validated {
public:

  Validated();
  // invalid constructor

  Validated(const T& data);
  // valid constructor

  bool valid() const;
  // is this valid or not?

  void invalidate();
  // makes the class invalid again, so call in a function which will change the
  // cached value.

  void set_data(const T& data);
  // set the data.

  operator T();
  // implicit conversion to the template type.

private:

  bool m_valid;
  T m_data;

};

//=============================================================================
template <typename T>
Validated<T>::Validated()
//
//D Invalid constructor
//
  : m_valid(false),
    m_data(0)
{
}

//=============================================================================
template <typename T>
Validated<T>::Validated(const T& data)
//
//D Valid constructor
//
  : m_valid(true),
    m_data(&data)
{
}

//=============================================================================
template <typename T>
bool Validated<T>::valid() const
//
//D is this valid or not?
//
{
  return m_valid;
}

//=============================================================================
template <typename T>
void Validated<T>::invalidate()
//
//D Makes the class invalid again, so call when the client calls a function
//D which will change the cached value.
//
{
  m_valid = false;
  m_data = 0;
}

//=============================================================================
template <typename T>
void Validated<T>::set_data(const T& data)
//
//D set the data.
//
{
  m_data = data;
  m_valid = true;
}

//=============================================================================
template <typename T>
Validated<T>::operator T()
//
//D implicit conversion to the template type.
//
{
  // a nice way of returning a message with a standard assert.
  assert(valid() && "Cannot return invalid data.");
  return m_data;
}

//=============================================================================
class Triangle {
public:

  Triangle(const Point& point_1, const Point& point_2, const Point& point_3);
  // Constructor, points should be entered anti-clockwise.

  void set_first_point(const Point& point);
  // Sets the first point

  double area() const;
  // Returns the area

private:

  Point m_point_1;
  Point m_point_2;
  Point m_point_3;
  
  mutable Validated<double> m_area;
  // this is mutable as it is used as a cache in area() which is a logically
  // const method
};

//=============================================================================
Triangle::Triangle(
  const Point& point_1,
  const Point& point_2,
  const Point& point_3
)
//
//D Copy the values from the passed in points.
//
  : m_point_1(point_1.x, point_1.y),
    m_point_2(point_2.x, point_2.y),
    m_point_3(point_3.x, point_3.y)
{
}

//=============================================================================
double Triangle::area() const
//
//D Returns the area, first time it works it out it caches the result.
//
{
  if (!m_area.valid()) {
    // work out the area using 1/2 ab sin(C)
    
    // a is the length between point 1 and point 2
    double a = std::sqrt(
      (m_point_2.x - m_point_1.x) * (m_point_2.x - m_point_1.x) +
      (m_point_2.y - m_point_1.y) * (m_point_2.y - m_point_1.y)
    );

    // b is the length between point 2 and point 3
    double b = std::sqrt(
      (m_point_3.x - m_point_2.x) * (m_point_3.x - m_point_2.x) +
      (m_point_3.y - m_point_2.y) * (m_point_3.y - m_point_2.y)
    );

    // c is the length between point 3 and point 1
    double c = std::sqrt(
      (m_point_1.x - m_point_3.x) * (m_point_1.x - m_point_3.x) +
      (m_point_1.y - m_point_3.y) * (m_point_1.y - m_point_3.y)
    );

    // use the cosine rule cos(C) = (a^2 + b^2 - c^2) / 2ab
    double cos_C = (a*a + b*b - c*c) / (2 * a * b);
    m_area.set_data(0.5 * a * b * std::sin(std::acos(cos_C)));
    
    // output to demonstrate which path is being taken
    std::cout << "Area calculated." << std::endl;
  } else {
    // this else is only here to show the cached value is being used
    std::cout << "Cached area returned." << std::endl;
  }
  return m_area;
}

//=============================================================================
void Triangle::set_first_point(const Point& point)
//
//D Sets the first point, useful to demonstrate invalidating the cached area.
//
{
  m_point_1.x = point.x;
  m_point_1.y = point.y;
  m_area.invalidate();
}

//=============================================================================
TEST(Triangle, caching)
{
  std::stringstream ss;
  // Save old buffer
  auto cout_buffer = std::cout.rdbuf();
  // Redirect std::cout to ss.
  std::cout.rdbuf(ss.rdbuf());

  Point one(0, 0);
  Point two(5, 0);
  Point three(5, 1);
  Triangle tri(one, two, three);
  tri.area();
  TEST_EQUAL(ss.str(), "Area calculated.\n");
  ss.str("");

  tri.area();
  TEST_EQUAL(ss.str(), "Cached area returned.\n");
  ss.str("");
  
  tri.set_first_point(Point(1, 0));
  tri.area();
  TEST_EQUAL(ss.str(), "Area calculated.\n");

  // Direct std::cout back to it's original buffer.
  std::cout.rdbuf(cout_buffer);
}

//=============================================================================
TEST(Triangle, area)
{
  Point one(1, 0);
  Point two(0, 1);
  Point three(0, 0);
  Triangle tri(one, two, three);
  double area = tri.area();
  TEST_APPROX_EQUAL(area, 0.5, 0.0000001);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
