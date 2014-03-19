//=============================================================================
//
// Inspired by the Visitor pattern in
// http://isa.unomaha.edu/wp-content/uploads/2012/08/Design-Patterns.pdf

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "UnitTest.h"

using namespace std;

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
  friend class utest_Visitor;
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

  Wheel(string name)
    : m_name(name)
    {}

  string name() const
    {
      return m_name;
    }
  
  void accept(IVisitor& visitor) override
    {
      visitor.visit(*this);
    }

private:
  string m_name;
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
      cout << "Wheel " << wheel.name() << endl;
    }

  virtual void visit(Body& wheel) override
    {
      cout << "Body" << endl;
    }

  virtual void visit(Car& wheel) override
    {
      cout << "Car" << endl;
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

  virtual void visit(Body& wheel) override
    {
      m_body_visited = true;
    }

  virtual void visit(Car& wheel) override
    {
      m_car_visited = true;
    }
private:

  friend class utest_Visitor;

  vector<string> m_wheels_visited;
  bool m_car_visited;
  bool m_body_visited;
};
  
//=============================================================================
class utest_Visitor : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_visit();
  }

private:

  void test_visit();

};

//=============================================================================
void utest_Visitor::test_visit()
{
  print(DGC_CURRENT_FUNCTION);
  Car car;
  Visitor visitor;
  car.accept(visitor);
  test(
    visitor.m_wheels_visited.size() == 4,
    "Wrong number of wheels visited."
  );
  auto pos = find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Front Left"
  );
  test(pos != visitor.m_wheels_visited.end(), "Did not find \"Front Left\"");
  pos = find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Front Right"
  );
  test(pos != visitor.m_wheels_visited.end(), "Did not find \"Front Right\"");
  pos = find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Back Left"
  );
  test(pos != visitor.m_wheels_visited.end(), "Did not find \"Back Left\"");
  pos = find(
    visitor.m_wheels_visited.begin(),
    visitor.m_wheels_visited.end(),
    "Back Right"
  );
  test(pos != visitor.m_wheels_visited.end(), "Did not find \"Back Right\"");
  test(visitor.m_body_visited, "Did not visit body.");
  test(visitor.m_car_visited, "Did not visit car.");
}

//=============================================================================
int main() {
  utest_Visitor test;
  test.run_tests();
  return 0;
}

