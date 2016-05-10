//=============================================================================
//
// Inspired by the Visitor pattern in
// http://isa.unomaha.edu/wp-content/uploads/2012/08/Design-Patterns.pdf

#include "Capabilities.h"
#if defined(CAPABILITY_USER_DEFINED_LITERALS) && defined(CAPABILITY_CONSTEXPR)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <UnitCpp.h>

#include "size_t_literal.h"

class ICarElement;
class Wheel;
class Body;
class Car;

//=============================================================================
class IVisitor {
public:
  virtual void visit(Wheel& wheel) = 0;
  virtual void visit(Body& wheel) = 0;
  virtual void visit(Car& wheel) = 0;
  
  virtual ~IVisitor() = 0;
private:
  UNITCPP_FRIEND_TEST(Visitor, visit);
};

IVisitor::~IVisitor(){}

//=============================================================================
class ICarElement {
public:
  virtual void accept(IVisitor& visitor) = 0;

  virtual ~ICarElement() = 0;
};
ICarElement::~ICarElement(){}

//=============================================================================
class Wheel : public ICarElement {
public:

  Wheel(std::string name)
    : m_name(name)
    {}

  std::string name() const
    {
      return m_name;
    }
  
  void accept(IVisitor& visitor) override
    {
      visitor.visit(*this);
    }

private:
  std::string m_name;
};

//=============================================================================
class Body : public ICarElement {
public:

  void accept(IVisitor& visitor) override
    {
      visitor.visit(*this);
    }

private:
};

//=============================================================================
class Car : public ICarElement {
public:

  Car()
    : m_front_left_wheel("Front Left"),
      m_front_right_wheel("Front Right"),
      m_back_left_wheel("Back Left"),
      m_back_right_wheel("Back Right"),
      m_body()
    {}
  
  void accept(IVisitor& visitor) override
    {
      visitor.visit(m_front_left_wheel);
      visitor.visit(m_front_right_wheel);
      visitor.visit(m_back_left_wheel);
      visitor.visit(m_back_right_wheel);
      visitor.visit(m_body);
      visitor.visit(*this);
    }

private:
  Wheel m_front_left_wheel;
  Wheel m_front_right_wheel;
  Wheel m_back_left_wheel;
  Wheel m_back_right_wheel;
  Body m_body;
};


//=============================================================================
class PrintVisitor : public IVisitor {
public:

  virtual void visit(Wheel& wheel) override
    {
      std::cout << "Wheel " << wheel.name() << std::endl;
    }

  virtual void visit(Body&) override
    {
      std::cout << "Body" << std::endl;
    }

  virtual void visit(Car&) override
    {
      std::cout << "Car" << std::endl;
    }
};
  
//=============================================================================
class Visitor : public IVisitor {
public:

  Visitor()
    : m_wheels_visited(),
      m_car_visited(false),
      m_body_visited(false)
    {}
  
  virtual void visit(Wheel& wheel) override
    {
      m_wheels_visited.push_back(wheel.name());
    }

  virtual void visit(Body&) override
    {
      m_body_visited = true;
    }

  virtual void visit(Car&) override
    {
      m_car_visited = true;
    }
private:

  UNITCPP_FRIEND_TEST(Visitor, visit);
  
  std::vector<std::string> m_wheels_visited;
  bool m_car_visited;
  bool m_body_visited;
};
  
//=============================================================================
TEST(Visitor, visit)
{
  Car car;
  Visitor visitor;
  car.accept(visitor);
  TEST_EQUAL(
    visitor.m_wheels_visited.size(),
    4_st,
    "Wrong number of wheels visited."
  );
  auto pos = std::find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Front Left"
  );
  TEST_NOT_EQUAL(
    pos,
    visitor.m_wheels_visited.end(),
    "Did not find \"Front Left\""
  );
  pos = std::find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Front Right"
  );
  TEST_NOT_EQUAL(
    pos,
    visitor.m_wheels_visited.end(),
    "Did not find \"Front Right\""
  );
  pos = std::find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Back Left"
  );
  TEST_NOT_EQUAL(
    pos,
    visitor.m_wheels_visited.end(),
    "Did not find \"Back Left\""
  );
  pos = std::find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Back Right"
  );
  TEST_NOT_EQUAL(
    pos,
    visitor.m_wheels_visited.end(),
    "Did not find \"Back Right\""
  );
  TEST_TRUE(visitor.m_body_visited, "Did not visit body.");
  TEST_TRUE(visitor.m_car_visited, "Did not visit car.");
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

#else // defined(CAPABILITY_USER_DEFINED_LITERALS)
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_USER_DEFINED_LITERALS);
#endif
