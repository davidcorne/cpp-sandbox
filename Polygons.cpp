// from http://www.cplusplus.com/doc/tutorial/polymorphism/
// dynamic allocation and polymorphism
//
// Archetypal polygon example for inheritance. A base polygon, a derived
// rectangle and triangle. Not great as you use a width and height for the
// polygon but not all polygons have it. Also I prepended all the classes with
// the letter C and allocated the instances as pointers to the base class.

#include <iostream>

class CPolygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area (void) =0;
    void printarea (void)
    { std::cout << area() << std::endl; }
  virtual ~CPolygon() = 0;
  };

CPolygon::~CPolygon()
{
}

class CRectangle: public CPolygon {
  public:
    int area (void)
      { return (width * height); }
  };

class CTriangle: public CPolygon {
  public:
    int area (void)
      { return (width * height / 2); }
  };

int main () {
  CPolygon * ppoly1 = new CRectangle;
  CPolygon * ppoly2 = new CTriangle;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  ppoly1->printarea();
  ppoly2->printarea();
  delete ppoly1;
  delete ppoly2;
  return 0;
}
