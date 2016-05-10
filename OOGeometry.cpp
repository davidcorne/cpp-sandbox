//=============================================================================
// This is sort of how I would solve problems like this
// http://www.codeproject.com/Articles/803411/Data-Structures-in-Object-Oriented-Programming
// but in C++.

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS
#include <cassert>

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <vector>

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
  bool operator<(const ShapeType& other) const;
  
  ShapeType(const ShapeType& type);
  ShapeType& operator=(const ShapeType& type);

  ~ShapeType();
  
private:

  int m_id;
  static int s_id_creator;
};

//=============================================================================
class IShape {
public:

  IShape();

  virtual ShapeType type() const = 0;
  
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
  
  virtual ShapeType type() const override;

  static ShapeType shape_type();
  
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

  virtual ShapeType type() const override;

  static ShapeType shape_type();
  
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
typedef
  std::function<std::unique_ptr<IDrawableShape>(const IShape&)>
  DrawableCreator;

//=============================================================================
class DrawableCreatorRegister {
public:
  
  DrawableCreatorRegister();
  // Constructor

  void register_creator(ShapeType type, DrawableCreator creator);
  // Register a creator for a shape type.
  
  DrawableCreator creator(ShapeType type) const;
  // Return a creator for a shape type.
  
  ~DrawableCreatorRegister();
  // Destructor

private:

  std::map<ShapeType, DrawableCreator> m_creation_map;
};

//=============================================================================
class DrawableShapeFactory {
public:

  DrawableShapeFactory(const DrawableCreatorRegister& creator_register);

  std::unique_ptr<IDrawableShape> create_drawable_shape(
    const IShape& shape
  ) const;
  
  ~DrawableShapeFactory();

private:

  DrawableShapeFactory(const DrawableShapeFactory&);
  DrawableShapeFactory& operator=(const DrawableShapeFactory&);

  const DrawableCreatorRegister& m_creator_register;
};

//=============================================================================
class DrawableTriangle : public IDrawableShape {
public:

  DrawableTriangle(Triangle tri);

  virtual void draw(ICanvas& canvas) override;
  
  virtual ~DrawableTriangle();

private:

  Triangle m_triangle;
};

//=============================================================================
class DrawableRectangle : public IDrawableShape {
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
template <typename tSHAPE, typename tDRAWABLE_SHAPE>
std::unique_ptr<IDrawableShape> create_drawable(const IShape& shape);

//=============================================================================
int main()
{
  DrawableCreatorRegister drawable_register;
  drawable_register.register_creator(
    Triangle::shape_type(),
    create_drawable<Triangle, DrawableTriangle>
  );
  drawable_register.register_creator(
    Rectangle::shape_type(),
    create_drawable<Rectangle, DrawableRectangle>
  );
  DrawableShapeFactory factory(drawable_register);
  
  std::vector<std::unique_ptr<IShape> > database;
  database.emplace_back(new Triangle({0,0}, {0,1}, {1,0}));
  database.emplace_back(new Rectangle({0,5}, {5,1}));

  std::vector<std::unique_ptr<IDrawableShape> > drawables;
  for (const auto& shape: database) {
    drawables.push_back(factory.create_drawable_shape(*shape));
  }

  ConsoleCanvas canvas(std::cout);
  for (auto& drawable_shape: drawables) {
    drawable_shape->draw(canvas);
    std::cout << "\n";
  }
  return 0;
}

//----- IShape

IShape::IShape() {}
IShape::~IShape() {}

//----- ShapeType
int ShapeType::s_id_creator(0);

//=============================================================================
ShapeType::ShapeType()
  : m_id(++s_id_creator)
{
}

//=============================================================================
ShapeType::ShapeType(const ShapeType& other)
  : m_id(other.m_id)
{
}

//=============================================================================
ShapeType& ShapeType::operator=(const ShapeType& other)
{
  if (&other != this) {
    m_id = other.m_id;
  }
  return *this;
}

//=============================================================================
bool ShapeType::operator==(const ShapeType& other) const
{
  return other.m_id == m_id;
}

//=============================================================================
bool ShapeType::operator<(const ShapeType& other) const
{
  return other.m_id < m_id;
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
ShapeType Triangle::type() const
{
  return shape_type();
}

//=============================================================================
ShapeType Triangle::shape_type()
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
ShapeType Rectangle::type() const
{
  return shape_type();
}

//=============================================================================
ShapeType Rectangle::shape_type()
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

//----- DrawableCreatorRegister
//=============================================================================
DrawableCreatorRegister::DrawableCreatorRegister()
{
}

//=============================================================================
DrawableCreatorRegister::~DrawableCreatorRegister()
{
}

//=============================================================================
DrawableCreator DrawableCreatorRegister::creator(ShapeType shape_type) const
{
  return m_creation_map.at(shape_type);
}

void DrawableCreatorRegister::register_creator(
  ShapeType shape_type,
  DrawableCreator creator
)
{
  m_creation_map.insert(std::make_pair(shape_type, creator));
}

//----- DrawableShapeFactory
//=============================================================================
DrawableShapeFactory::DrawableShapeFactory(
  const DrawableCreatorRegister& creator_register
)
  : m_creator_register(creator_register)
{
}

//=============================================================================
std::unique_ptr<IDrawableShape> DrawableShapeFactory::create_drawable_shape(
  const IShape& shape
) const
{
  return m_creator_register.creator(shape.type())(shape);
}
  
//=============================================================================
DrawableShapeFactory::~DrawableShapeFactory()
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

//=============================================================================
template <typename tSHAPE, typename tDRAWABLE_SHAPE>
std::unique_ptr<IDrawableShape> create_drawable(const IShape& shape)
{
  const tSHAPE* derived_shape = dynamic_cast<const tSHAPE*>(&shape);
  assert(derived_shape && "dynamic_cast should be valid.");
  return std::unique_ptr<IDrawableShape>(new tDRAWABLE_SHAPE(*derived_shape));
}

#else
#include "UnsupportedFeatureMain.h"
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif
