// from http://www.cplusplus.com/doc/tutorial/polymorphism/
// dynamic allocation and polymorphism
//
// Archetypal polygon example for inheritance. A base polygon, a derived
// rectangle and triangle. Not great as you use a width and height for the
// polygon but not all polygons have it. Also I prepended all the classes with
// the letter C and allocated the instances as pointers to the base class.

#include <iostream>
#include <memory>

//=============================================================================
class CPolygon {
public:

  void set_values(int a, int b) {
     width=a;
     height=b;
  }
  
  virtual int area() const = 0;
  
  virtual ~CPolygon() = 0;
  
protected:
  int width;
  int height;
};

//=============================================================================
void printarea(const CPolygon& poly)
{
  std::cout << poly.area() << std::endl;
}

//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
class CRectangle: public CPolygon {
public:
  int area() const override {
    return (width * height);
  }
};

//=============================================================================
class CTriangle: public CPolygon {
public:
  int area() const override {
    return (width * height / 2);
  }
};

//=============================================================================
int main () {
  std::unique_ptr<CPolygon> ppoly1 = std::make_unique<CRectangle>();
  std::unique_ptr<CPolygon> ppoly2 = std::make_unique<CTriangle>();
  ppoly1->set_values(4,5);
  ppoly2->set_values(4,5);
  printarea(*ppoly1);
  printarea(*ppoly2);
  return 0;
}
