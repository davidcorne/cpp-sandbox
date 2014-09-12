//=============================================================================
// This is sort of how I would solve problems like this
// http://www.codeproject.com/Articles/803411/Data-Structures-in-Object-Oriented-Programming
// but in C++.

#include <iostream>
#include <map>
#include <memory>

//=============================================================================
// Would probably have a class and encapsulation here, but never mind.
struct Point {
  double x;
  double y;
};

//=============================================================================
class ShapeType {
public:

  ShapeType();

  bool operator==(const ShapeType& other) const;
  
  ~ShapeType();
  
private:

  ShapeType(const ShapeType& type);
  ShapeType& operator=(const ShapeType& type);

};

//=============================================================================
class IShape {
public:

  IShape();

  virtual const ShapeType& type() const = 0;
  
  virtual ~IShape() = 0;
};

//=============================================================================
class Triangle : public IShape {
public:

  Triangle(Point one, Point two, Point three);

  Triangle(const Triangle& tri);
  
  Triangle& operator=(const Triangle& tri);

  Point one() const;
  
  Point two() const;
  
  Point three() const;
  
  virtual const ShapeType& type() const override;

  static const ShapeType& shape_type();
  
  virtual ~Triangle();
  
private:

  Point m_one;
  Point m_two;
  Point m_three;
};

//=============================================================================
class Rectangle : public IShape {
public:

  Rectangle(Point top_left, Point bottom_right);

  Rectangle(const Rectangle& rectangle);
  Rectangle& operator=(const Rectangle& rectangle);

  Point top_left() const;

  Point bottom_right() const;

  virtual const ShapeType& type() const override;
  
  virtual ~Rectangle();
  
private:

  Point m_top_left;
  Point m_bottom_right;
};

//=============================================================================
class ICanvas {
public:

  ICanvas();

  virtual void draw_line(Point a, Point b) = 0;

  virtual ~ICanvas() = 0;
  
private:

  ICanvas(const ICanvas&);
  ICanvas& operator=(const ICanvas&);
  
};

//=============================================================================
class IDrawableShape {
public:

  IDrawableShape();

  virtual void draw(ICanvas& canvas) = 0;
  
  virtual ~IDrawableShape() = 0;
  
private:
  
  IDrawableShape(const IDrawableShape&);
  IDrawableShape& operator=(const IDrawableShape&);
  
};

//=============================================================================
class DrawableRegistrar {
public:

  typedef
    std::function<std::unique_ptr<IDrawableShape>(const IShape&)>
    DrawableCreator;
  
  DrawableRegistrar(const ShapeType& type, DrawableCreator creator);

  static DrawableCreator drawable_creator(const ShapeType& type);
  
  ~DrawableRegistrar();

private:

  static std::map<const ShapeType*, DrawableCreator> s_creation_map;
  
};

//=============================================================================
class DrawableTriangle : IDrawableShape {
public:

  DrawableTriangle(Triangle tri);

  virtual void draw(ICanvas& canvas) override;
  
  virtual ~DrawableTriangle();

private:
  static const DrawableRegistrar s_registra(
    Triangle::shape_type(),
    [](const IShape& shape){return std::unique_ptr<IDrawableShape>(
        new DrawableTriangle(dynamic_cast<const Triangle&>(shape))
      );
    }
  );
  Triangle m_triangle;
};

//=============================================================================
class DrawableRectangle : IDrawableShape {
public:

  DrawableRectangle(Rectangle rectangle);

  virtual void draw(ICanvas& canvas) override;
  
  virtual ~DrawableRectangle();

private:

  Rectangle m_rectangle;
};

//=============================================================================
class ConsoleCanvas : public ICanvas {
public:

  ConsoleCanvas(std::ostream& os);

  virtual void draw_line(Point a, Point b) override;

  virtual ~ConsoleCanvas();

private:

  ConsoleCanvas(const ConsoleCanvas&);
  ConsoleCanvas& operator=(const ConsoleCanvas&);

  std::ostream& m_os;
};

//=============================================================================
std::unique_ptr<IDrawableShape> create_drawable_shape(const IShape& shape);

//=============================================================================
int main()
{
  Triangle tri({0,0}, {0,1}, {1,0});
  Rectangle rect({0, 5}, {5, 0});
  
  ConsoleCanvas canvas(std::cout);
  create_drawable_shape(tri)->draw(canvas);
  std::cout << "\n";
  DrawableRectangle(rect).draw(canvas);
  return 0;
}

//----- IShape

IShape::IShape() {}
IShape::~IShape() {}

//----- ShapeType
ShapeType::ShapeType()
{
}

//=============================================================================
bool ShapeType::operator==(const ShapeType& other) const
{
  return &other == this;
}

//=============================================================================
ShapeType::~ShapeType()
{
}

//----- Triangle

//=============================================================================
Triangle::Triangle(Point one, Point two, Point three)
  : m_one(one),
    m_two(two),
    m_three(three)
{

}

//=============================================================================
Triangle::Triangle(const Triangle& tri)
  : m_one(tri.one()),
    m_two(tri.two()),
    m_three(tri.three())
{
}

//=============================================================================
Triangle& Triangle::operator=(const Triangle& tri)
{
  if (&tri != this) {
    m_one = tri.one();
    m_two = tri.two();
    m_three = tri.three();
  }
  return *this;
}

//=============================================================================
Point Triangle::one() const
{
  return m_one;
}

//=============================================================================
Point Triangle::two() const
{
  return m_two;
}

//=============================================================================
Point Triangle::three() const
{
  return m_three;
}

//=============================================================================
const ShapeType& Triangle::type() const
{
  static ShapeType triangle_type;
  return triangle_type;
}

//=============================================================================
Triangle::~Triangle()
{
}

//----- Rectangle

//=============================================================================
Rectangle::Rectangle(Point top_left, Point bottom_right)
  : m_top_left(top_left),
    m_bottom_right(bottom_right)
{
}

//=============================================================================
Rectangle::Rectangle(const Rectangle& rect)
  : m_top_left(rect.top_left()),
    m_bottom_right(rect.bottom_right())
{
}

//=============================================================================
Rectangle& Rectangle::operator=(const Rectangle& rect)
{
  if (&rect != this) {
    m_top_left = rect.top_left();
    m_bottom_right = rect.bottom_right();
  }
  return *this;
}

//=============================================================================
Point Rectangle::top_left() const
{
  return m_top_left;
}

//=============================================================================
Point Rectangle::bottom_right() const
{
  return m_bottom_right;
}

//=============================================================================
const ShapeType& Rectangle::type() const
{
  static ShapeType rectangle_type;
  return rectangle_type;
}

//=============================================================================
Rectangle::~Rectangle()
{
}

//----- IDrawableShape
IDrawableShape::IDrawableShape() {}
IDrawableShape::~IDrawableShape() {}

//----- DrawableRegistrar

//=============================================================================
DrawableRegistrar::DrawableRegistrar(
  const ShapeType& type,
  DrawableRegistrar::DrawableCreator creator
)
{
  s_creation_map[&type] = creator;
}

//----- DrawableTriangle

//=============================================================================
DrawableTriangle::DrawableTriangle(Triangle tri)
  : m_triangle(tri)
{
}

//=============================================================================
void DrawableTriangle::draw(ICanvas& canvas)
{
  canvas.draw_line(m_triangle.one(), m_triangle.two());
  canvas.draw_line(m_triangle.two(), m_triangle.three());
  canvas.draw_line(m_triangle.three(), m_triangle.one());
}

//=============================================================================
DrawableTriangle::~DrawableTriangle()
{
}

//----- DrawableRectangle

//=============================================================================
DrawableRectangle::DrawableRectangle(Rectangle rect)
  : m_rectangle(rect)
{
}

//=============================================================================
void DrawableRectangle::draw(ICanvas& canvas)
{
  Point top_right = {m_rectangle.bottom_right().x, m_rectangle.top_left().y};
  Point bottom_left = {m_rectangle.top_left().x, m_rectangle.bottom_right().y};
  canvas.draw_line(m_rectangle.top_left(), top_right);
  canvas.draw_line(top_right, m_rectangle.bottom_right());
  canvas.draw_line(m_rectangle.bottom_right(), bottom_left);
  canvas.draw_line(bottom_left, m_rectangle.top_left());
}

//=============================================================================
DrawableRectangle::~DrawableRectangle()
{
}
   
//----- ICanvas

ICanvas::ICanvas() {}
ICanvas::~ICanvas() {}

//----- ConsoleCanvas

//=============================================================================
ConsoleCanvas::ConsoleCanvas(std::ostream& os)
  : m_os(os)
{
}

//=============================================================================
void ConsoleCanvas::draw_line(Point a, Point b)
{
  m_os
    << "Line: ("
    << a.x
    << ","
    << a.y
    << ") -> ("
    << b.x
    << ","
    << b.y
    << ")\n";
}

//=============================================================================
ConsoleCanvas::~ConsoleCanvas()
{
}

//----- create_drawable_shape()

//=============================================================================
std::unique_ptr<IDrawableShape> create_drawable_shape(const IShape& shape)
{
  return DrawableRegistrar::drawable_creator(shape.type())(shape);
}
