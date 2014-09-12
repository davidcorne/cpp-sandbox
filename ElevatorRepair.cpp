//=============================================================================
//
// This is sort of vauguely inspired by this:
// http://talesofcpp.fusionfenix.com/post-4/episode-three-friends-with-benefits?utm_content=bufferbcb4a&utm_medium=social&utm_source=plus.google.com&utm_campaign=buffer

#include <iostream>
#include <memory>
#include <cmath>

typedef double Floor;

//=============================================================================
class IElevator {
public:

  IElevator();
  
  virtual ~IElevator() = 0;

  virtual void go_to_floor(Floor floor) = 0;

  virtual bool broken() const = 0;

  virtual Floor floor() const = 0;
  
private:

  friend class ElevatorRepairMan;

  virtual void fix_break() = 0;
  // Fix the broken elevator.
  
};

//=============================================================================
class ElevatorRepairMan {
public:

  ElevatorRepairMan();
  
  ~ElevatorRepairMan();

  void fix_elevator(IElevator& elevator);
  // Could be const, but I feel that if this was "properly" implemented he
  // would use tools (which wears them) and use screws etc.
  
private:

  ElevatorRepairMan(const ElevatorRepairMan&);
  ElevatorRepairMan& operator=(const ElevatorRepairMan&);
  // You can't copy a person!
  
};

//=============================================================================
class Elevator : public IElevator {
public:

  Elevator();
  
  virtual ~Elevator();

  virtual void go_to_floor(Floor floor) override;

  virtual Floor floor() const override;
  
  virtual bool broken() const override;
  
private:

  virtual void fix_break() override;

  bool valid() const;
  // Is the floor I'm on valid?
  
  bool m_broken;
  Floor m_floor;
};

std::ostream& operator<<(std::ostream& os, const IElevator& elevator);

//=============================================================================
int main()
{
  std::cout.precision(1);
  std::cout << std::boolalpha << std::fixed;
  
  std::unique_ptr<IElevator> elevator(new Elevator);
  elevator->go_to_floor(2);
  std::cout << *elevator << std::endl;

  elevator->go_to_floor(0.5);
  std::cout << *elevator << std::endl;
  
  elevator->go_to_floor(0);
  std::cout << *elevator << std::endl;

  // oh no! it must be broken!
  ElevatorRepairMan repair_man;
  repair_man.fix_elevator(*elevator);
  std::cout << *elevator << std::endl;

  elevator->go_to_floor(3);
  std::cout << *elevator << std::endl;

  return 0;
}

//---- IElevator
IElevator::IElevator() {}
IElevator::~IElevator() {}

//----- ElevatorRepairMan
ElevatorRepairMan::ElevatorRepairMan() {}
ElevatorRepairMan::~ElevatorRepairMan() {}

//=============================================================================
void ElevatorRepairMan::fix_elevator(IElevator& elevator)
{
  elevator.fix_break();
}

//----- Elevator
Elevator::Elevator()
  : m_broken(false),
    m_floor(0)
{
}
Elevator::~Elevator() {}

//=============================================================================
void Elevator::go_to_floor(Floor floor)
{
  if (!broken()) {
    m_floor = floor;
    if (!valid()) {
      // we've gone to an invalid floor!
      m_broken = true;
    }
  }
}

//=============================================================================
bool Elevator::broken() const
{
  return m_broken;
}

//=============================================================================
void Elevator::fix_break()
{
  m_broken = false;
  m_floor = 0;
}

//=============================================================================
bool Elevator::valid() const
{
  Floor int_part;
  Floor fraction_part = std::modf(m_floor, &int_part);
  return fraction_part == 0;
}

Floor Elevator::floor() const
{
  return m_floor;
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, const IElevator& elevator)
{
  os
    << "Elevator {floor="
    << elevator.floor()
    << ", broken="
    << elevator.broken()
    << "}";
  return os;  
}
