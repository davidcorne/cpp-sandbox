//=============================================================================
//
// 

#include <UnitCpp/Test.h>

//=============================================================================
class Point {
public:

  Point(double a, double b);
  Point(const Point& point);
  Point& operator=(const Point& point);
  ~Point();

  double a() const;
  double b() const;

private:

  friend bool operator<(const Point&, const Point&);

  double m_a;
  double m_b;
};

//=============================================================================
bool operator<(const Point& a, const Point& b)
{
  // compares the points lexically.
  return std::tie(a.m_a, a.m_b) < std::tie(b.m_a, b.m_b);
}

//=============================================================================
Point::Point(double a, double b)
  : m_a(a),
    m_b(b)
{
}

//=============================================================================
Point::~Point() = default;
Point::Point(const Point& point) = default;
Point& Point::operator=(const Point& point) = default;

//=============================================================================
double Point::a() const
{
  return m_a;
}

//=============================================================================
double Point::b() const
{
  return m_b;
}

//=============================================================================
TEST(Tie, a)
{
  Point a(0, 1);
  Point b(0, 0);
  TEST_LESS_THAN(b, a);
}

//=============================================================================
int main() {
  return UnitCpp::TestRegister::test_register().run_tests();
}