//=============================================================================
//
// 

#include <UnitCpp.h>
#include <tuple>

//=============================================================================
class Point {
public:

  Point(double a, double b);
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
Point::~Point()
{
}

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
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
