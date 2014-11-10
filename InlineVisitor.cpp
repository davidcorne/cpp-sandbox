//=============================================================================
// Idea from:
// http://accu.org/index.php/journals/2021?utm_content=buffer2980b&utm_medium=social&utm_source=plus.google.com&utm_campaign=buffer


//not 100% sure why, but this only works on clang.
#include "Compiler.h"

#if COMPILER_TYPE == COMPILER_TYPE_CLANG
#include <iostream>

//----- Visitor stuff
template <typename T,
          typename F,
          typename BaseInner,
          typename ArgsT>
struct ComposeVisitor
{
  struct Inner : public BaseInner
  {
    using BaseInner::visit;
    Inner(ArgsT&& args) :
      BaseInner(std::move(args.second)),
      m_f(std::move(args.first))
    {
    }
    virtual void visit(T& t) final override
    {
      m_f(t);
    }
  private:
    F m_f;
  };
  ComposeVisitor(ArgsT&& args) :
    m_args(std::move(args))
  {
  }
  template <typename Tadd,
            typename Fadd>
  ComposeVisitor<
    Tadd,
    Fadd,
    Inner,
    std::pair<Fadd, ArgsT>> on(Fadd&& f)
  {
    return ComposeVisitor<
      Tadd,
      Fadd,
      Inner,
      std::pair<Fadd, ArgsT>>(
        std::make_pair(
          std::move(f),
          std::move(m_args)));
  }
  Inner end_visitor()
  {
    return Inner(std::move(m_args));
  }
  
  ArgsT m_args;
};
template <typename TVisitorBase>
struct EmptyVisitor
{
  struct Inner : public TVisitorBase
  {
    using TVisitorBase::visit;
    Inner(std::nullptr_t) {}
  };
  
  template <typename Tadd, typename Fadd>
  ComposeVisitor<
    Tadd,
    Fadd,
    Inner,
    std::pair<Fadd, std::nullptr_t>> on(Fadd&& f)
  {
    return ComposeVisitor<
      Tadd,
      Fadd,
      Inner,
      std::pair<Fadd, std::nullptr_t>>(
        std::make_pair(
          std::move(f),
          nullptr));
  }
};
template <typename TVisitorBase>
EmptyVisitor<TVisitorBase> begin_visitor()
{
  return EmptyVisitor<TVisitorBase>();
}

struct Triangle;
struct Square;

struct PolygonVisitor {

  virtual void visit(Triangle& t) = 0;
  virtual void visit(Square& s) = 0;
  
};

//=============================================================================
struct Polygon {
  virtual void accept(PolygonVisitor& v) = 0;
};

//=============================================================================
struct Square : public Polygon {
  virtual void accept(PolygonVisitor& v) override {
    v.visit(*this);
  }
};

//=============================================================================
struct Triangle : public Polygon {
  virtual void accept(PolygonVisitor& v) override {
    v.visit(*this);
  }
};

int count_sides(Polygon& polygon)
{
  int sides = 0;
  auto visitor = begin_visitor<PolygonVisitor>()
    .on<Triangle>([&sides](Triangle&){sides = 3;})
    .on<Square>([&sides](Square&){sides = 4;}).end_visitor();
  polygon.accept(visitor);
  return sides;
                
}

//=============================================================================
int main()
{
  Square square;
  Triangle triangle;
  std::cout
    << "Square   has "
    << count_sides(square)
    << " sides.\n"
    << "Triangle has "
    << count_sides(triangle)
    << " sides.\n";
  return 0;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif
