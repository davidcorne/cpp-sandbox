#include <iostream>

//=============================================================================
struct polygon {
public:
  virtual void print_area();
  // returns the area

  virtual ~polygon() = 0;
protected:
  polygon();

  virtual double area() = 0;
};

//=============================================================================
polygon::polygon()
// ctor, do nothing
{
}

//=============================================================================
polygon::~polygon()
// dtor, do nothing
{
}

//=============================================================================
void polygon::print_area()
// prints area
{
  std::cout << area() << std::endl;
}

//=============================================================================
struct triangle : public polygon {
public:

  triangle(double width, double height);
  virtual ~triangle();
  
protected:

  virtual double area();

private:
  double m_width;
  double m_height;
};

//=============================================================================
triangle::triangle(double width, double height)
// ctor
  : m_width(width),
    m_height(height)
{
}

//=============================================================================
triangle::~triangle()
// dtor, do nothing
{
}

//=============================================================================
double triangle::area()
// returns the area
{
  return 0.5 * m_width * m_height;
}

// bloody stupid and not a template!!! Only here to show that you can use
// structs when you have declares that it is a class in a template.
template <class T>
void area(T shape)
{
  shape.print_area();
}

int main()
// main function
{
  triangle tri(4, 5);
  tri.print_area();
  area(tri);
}
