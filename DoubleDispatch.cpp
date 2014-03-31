//=============================================================================
//
// Inspired by item 31 in Scott Meyers "More Effective C++".

#include <functional>
#include <iostream>
#include <string>
#include <map>

#include "UnitTest.h"

using namespace std;

class GameObject;

//=============================================================================
class HitMap {
public:

  HitMap();
  
  function<void(GameObject&, GameObject&)> collision(
    string name_1,
    string name_2
  );

private:
  map<pair<string, string>, function<void(GameObject&, GameObject&)> > m_hit_map;
};

//=============================================================================
class Game {
public:
  Game();

  HitMap& hit_map()
    {
      return m_hit_map;
    }

private:
  HitMap m_hit_map;
};

static Game* GAME = 0;

//=============================================================================
struct GameObject {

  virtual string name() const
    {
      return m_name;
    }

  void collide(GameObject& object);
  
  virtual ~GameObject() = 0;

protected:
  GameObject(string type, string name)
    : m_type(type),
      m_name(name)
    {}

  string type() const
    {
      return m_type;
    }

private:
  string m_type;
  string m_name;
};

//=============================================================================
class Asteroid : public GameObject {
public:
  Asteroid(string name)
    : GameObject("Asteroid", name)
    {}
};

//=============================================================================
class SpaceShip : public GameObject {
public:
  SpaceShip(string name)
    : GameObject("SpaceShip", name)
    {}

protected:
  SpaceShip(string type, string name)
    : GameObject(type, name)
    {}
};

//=============================================================================
class MilitarySpaceShip : public SpaceShip {
public:
  MilitarySpaceShip(string name)
    : SpaceShip("MilitarySpaceShip", name)
    {}
  
};

//=============================================================================
class utest_DoubleDispatch : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_collision();
  }

private:

  void test_collision();

};

//=============================================================================
void utest_DoubleDispatch::test_collision()
{
  print(DGC_CURRENT_FUNCTION);
  Asteroid asteroid("MX-1");
  MilitarySpaceShip enterprise("Enterprise");
  enterprise.collide(asteroid);
  asteroid.collide(enterprise);
  SpaceShip trader("Trader");
  trader.collide(asteroid);
}

//=============================================================================
int main() {
  GAME = new Game;
  utest_DoubleDispatch test;
  test.run_tests();
  delete GAME;
  return 0;
}

//=============================================================================
Game::Game()
{
}



//=============================================================================
void GameObject::collide(GameObject& object)
{
  auto collide_function = GAME->hit_map().collision(
    type(),
    object.type()
  );
  collide_function(*this, object);
}

//=============================================================================
GameObject::~GameObject()
{}

//=============================================================================
function<void(GameObject&, GameObject&)> HitMap::collision(
  string name_1,
  string name_2
)
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
  cout << space_ship.name() << " collided with " << asteroid.name() << endl;
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
HitMap::HitMap()
{
  m_hit_map[make_pair("SpaceShip", "Asteroid")] = space_ship_collide_asteroid;
  m_hit_map[make_pair("Asteroid", "SpaceShip")] = asteroid_collide_space_ship;
  m_hit_map[make_pair("MilitarySpaceShip", "Asteroid")] = space_ship_collide_asteroid;
  m_hit_map[make_pair("Asteroid", "MilitarySpaceShip")] = asteroid_collide_space_ship;
}
