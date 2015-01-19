//=============================================================================
//
// This is a changed example from some user code. It involves an accidentally
// referenced global variable.

#include <cassert>
#include <cmath>

#include <UnitCpp.h>

//=============================================================================
struct Point {
  double x;
  double y;

  double distance(Point other);
};

double distance(Point a, Point b);

//=============================================================================
double algorithm_1()
{
  //... set up code
  Point max = {50, 3};
  Point min = {-7, 0};
  double distance = max.distance(min);
  assert(distance > 0 && "distance should be positive.");
  //... some more distance manipulation
  return distance;
}

//=============================================================================
double algorithm_2()
{
  //... set up code
  assert(distance > 0 && "distance should be positive."); // what is distance?

  Point max = {50, 3};
  Point min = {-7, 0};
  double distance = max.distance(min);
  //... some more distance manipulation
  return distance;
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
double Point::distance(Point other)
{
  return ::distance(*this, other);
}

//=============================================================================
double distance(Point a, Point b)
{
  return std::sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

//=============================================================================
TEST(Point, distance)
{
  Point a = {0, 0};
  Point b = {3, 4};
  TEST_EQUAL(distance(a, b), 5);
  TEST_EQUAL(a.distance(b), b.distance(a));
}
