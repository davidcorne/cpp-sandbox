//=============================================================================
//
// 

#include "Capabilities.h"
#if defined(CAPABILITY_VARIADIC_TEMPLATES) && defined(CAPABILITY_DEFAULTED_FUNCTIONS)
#include "DuckTyping.h"
#include <random>
#include <chrono>
#include <thread>
#include <cassert>

// construct a trivial random generator engine from a time-based seed:
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine GENERATOR(seed);

//=============================================================================
// Roll a D6
double D6()
{
  std::uniform_int_distribution<int> distribution(1,6);
  int dice_roll = distribution(GENERATOR);
  double roll = static_cast<double>(dice_roll);
  return roll;
}

//=============================================================================
Primitive attack(Object& attacker, Object& defender)
{
  double damage =
    (attacker["attack"].d() + D6()) -
    (defender["defence"].d());
  if (damage < 0) {
    damage = 0;
  }
  double hp = defender["hp"].d();
  defender["hp"].d(hp - damage);

  Primitive return_damage;
  return_damage.d(damage);
  return return_damage;
}

//=============================================================================
void print_health(const Object& one, const Object& two)
{
  print("");
  print(one["name"], ": ", one["hp"]);
  print(two["name"], ": ", two["hp"]);
  print("");
}

//=============================================================================
Primitive fight(Object& one, Object& two)
{
  Primitive damage;
  while (true) {
    damage = one("attack")(two);
    print(one["name"], " attacked ", two["name"], " for ", damage, " damage.");
    print_health(one, two);
    if (two["hp"].d() <= 0) break;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    damage = two("attack")(one);
    print(two["name"], " attacked ", one["name"], " for ", damage, " damage.");
    print_health(one, two);
    if (one["hp"].d() <= 0) break;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  Object dead = (one["hp"].d() <= 0) ? one.clone() : two.clone();
  assert(dead["hp"].d() <= 0);
  print(dead["name"], " died.");
  return Primitive();
}

//=============================================================================
Object create_hero()
{
  Object hero;
  hero["attack"] = Primitive().d(10);
  hero["defence"] = Primitive().d(5);
  hero["hp"] = Primitive().d(20);
  hero["name"] = Primitive().s("Harry");
  hero.set_method("attack") = attack;
  hero.set_method("fight") = fight;
  return hero;
}

//=============================================================================
Object create_enemy(
  std::string enemy_class,
  double attack_value,
  double defence,
  double hp
)
{
  Object enemy;
  enemy["attack"] = Primitive().d(attack_value);
  enemy["defence"] = Primitive().d(defence);
  enemy["class"] = Primitive().s(enemy_class);
  enemy["name"] = Primitive().s(enemy_class);
  enemy["hp"] = Primitive().d(hp);
  enemy.set_method("attack") = attack;
  return std::move(enemy);
}

//=============================================================================
// Prototype enemies to create others from.
const Object ORC = create_enemy("Orc", 5, 4, 15);
const Object GOBLIN = create_enemy("Goblin", 4, 3, 12);
const Object DRAGON = create_enemy("Dragon", 10, 10, 20);

//=============================================================================
Object random_enemy(
  double orc_weight,
  double goblin_weight,
  double dragon_weight
)
{
  std::discrete_distribution<int> distribution(
    {orc_weight, goblin_weight, dragon_weight}
  );
  int choice = distribution(GENERATOR);
  assert(0 <= choice && choice <= 2);
  Object enemy;
  if (choice == 0) {
    enemy = ORC.clone();
  } else if (choice == 1) {
    enemy = GOBLIN.clone();
  } else if (choice == 2) {
    enemy = DRAGON.clone();
  }
  return enemy;
}

//=============================================================================
// get user input from 
int user_input_range(std::initializer_list<std::string> input)
{
  print("Options:");
  int count = 0;
  for (std::string option: input) {
    print(count, ") ", option);
    ++count;
  }
  int option = -1;
  std::cin >> option;
  return option;
}

//=============================================================================
bool encounter(Object& hero, Object& enemy)
{
  print("You encounter an enemy ", enemy["class"]);
  print("What will you do?");
  int option = user_input_range({"Fight", "Run", "Sneak Past"});
  if (option == 0) {
    hero("fight")(enemy);
    print("");
  } else if (option == 1) {
    print("\nYOU CAN'T RUN!!!!!\n");
    encounter(hero, enemy);
  } else if (option == 2) {
    
  }
  bool ok = hero["hp"].d() > 0;
  return ok;
}

//=============================================================================
bool adventure()
{
  Object hero = create_hero();
  // 4 (weighted) random encounters, then a dragon
  Object enemy;
  enemy = random_enemy(50, 50, 1);

  bool alive = true;
  alive = encounter(hero, enemy);
  if (!alive) return alive;

  enemy = random_enemy(50, 50, 2);
  alive = encounter(hero, enemy);
  if (!alive) return alive;

  enemy = random_enemy(50, 50, 20);
  alive = encounter(hero, enemy);
  if (!alive) return alive;

  enemy = random_enemy(50, 50, 50);
  alive = encounter(hero, enemy);
  if (!alive) return alive;
  
  Object dragon = DRAGON.clone();
  alive = encounter(hero, dragon);
  return alive;
}

//=============================================================================
int main() {
  while (true) {
    bool succeeded = adventure();
    if (succeeded) {
      print("!!!Congratulations!!!");
      print("You have defeated the monsters and saved the kingdom.");
    } else {
      print("You have died.");
    }
    print("");
    print("Play again?");
    int input = user_input_range({"Yes", "No"});
    if (input == 1) break;
  }
  return 0;
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_VARIADIC_TEMPLATES)
#endif
