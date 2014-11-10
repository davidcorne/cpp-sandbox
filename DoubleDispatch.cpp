//=============================================================================
//
// Inspired by item 31 in Scott Meyers "More Effective C++".

#include <assert.h>
#include <functional>
#include <iostream>
#include <string>
#include <map>

#include <UnitCpp/Test.h>

class GameObject;

//=============================================================================
class HitMap {
public:

  static HitMap& get();
  
  std::function<void(GameObject&, GameObject&)> collision_function(
    std::string name_1,
    std::string name_2
  ) const;

private:
  HitMap();

  std::map<
    std::pair<std::string, std::string>,
    std::function<void(GameObject&, GameObject&)>
  > m_hit_map;
};

//=============================================================================
class GameObject {
public:
  virtual std::string name() const
    {
      return m_name;
    }

  void collide(GameObject& object);
  
  virtual ~GameObject() = 0;

protected:
  GameObject(std::string type, std::string name)
    : m_type(type),
      m_name(name)
    {}

  std::string type() const
    {
      return m_type;
    }

private:
  std::string m_type;
  std::string m_name;
};

//=============================================================================
class Asteroid : public GameObject {
public:
  Asteroid(std::string name)
    : GameObject("Asteroid", name)
    {}
};

//=============================================================================
class SpaceShip : public GameObject {
public:
  SpaceShip(std::string name)
    : GameObject("SpaceShip", name)
    {}

protected:
  SpaceShip(std::string type, std::string name)
    : GameObject(type, name)
    {}
};

//=============================================================================
class MilitarySpaceShip : public SpaceShip {
public:
  MilitarySpaceShip(std::string name)
    : SpaceShip("MilitarySpaceShip", name)
    {}
  
};

//=============================================================================
TEST(DoubleDispatch, collision)
{
  Asteroid asteroid("MX-1");
  MilitarySpaceShip enterprise("Enterprise");
  enterprise.collide(asteroid);
  asteroid.collide(enterprise);
  SpaceShip trader("Trader");
  trader.collide(asteroid);
  trader.collide(enterprise);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
void GameObject::collide(GameObject& object)
{
  auto collide_function = HitMap::get().collision_function(
    type(),
    object.type()
  );
  collide_function(*this, object);
}

//=============================================================================
GameObject::~GameObject()
{}

//=============================================================================
std::function<void(GameObject&, GameObject&)> HitMap::collision_function(
  std::string name_1,
  std::string name_2
) const
{
  auto name_pair = make_pair(name_1, name_2);
  auto it = m_hit_map.find(name_pair);
  assert(it != m_hit_map.end());
  return it->second;
}

//=============================================================================
void space_ship_collide_asteroid(
  GameObject& space_ship_go,
  GameObject& asteroid_go
)
{
  SpaceShip& space_ship = dynamic_cast<SpaceShip&>(space_ship_go);
  assert(&space_ship);
  Asteroid& asteroid = dynamic_cast<Asteroid&>(asteroid_go);
  assert(&asteroid);
  std::cout << space_ship.name() << " collided with " << asteroid.name() << std::endl;
}

//=============================================================================
void asteroid_collide_space_ship(
  GameObject& asteroid,
  GameObject& space_ship
)
{
  space_ship_collide_asteroid(space_ship, asteroid);
}

//=============================================================================
void space_ship_collide_space_ship(
  GameObject& ship_1,
  GameObject& ship_2
)
{
  std::cout << "Space ship collision." << std::endl;
}

//=============================================================================
HitMap::HitMap()
{
  m_hit_map[std::make_pair("SpaceShip", "Asteroid")] = space_ship_collide_asteroid;
  m_hit_map[std::make_pair("Asteroid", "SpaceShip")] = asteroid_collide_space_ship;

  m_hit_map[std::make_pair("MilitarySpaceShip", "Asteroid")] = space_ship_collide_asteroid;
  m_hit_map[std::make_pair("Asteroid", "MilitarySpaceShip")] = asteroid_collide_space_ship;

  m_hit_map[std::make_pair("MilitarySpaceShip", "SpaceShip")] = space_ship_collide_space_ship;
  m_hit_map[std::make_pair("SpaceShip", "MilitarySpaceShip")] = space_ship_collide_space_ship;
  m_hit_map[std::make_pair("SpaceShip", "SpaceShip")] = space_ship_collide_space_ship;
}

//=============================================================================
HitMap& HitMap::get()
{
  static HitMap hit_map;
  return hit_map;
}

