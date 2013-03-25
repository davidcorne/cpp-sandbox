// http://stackoverflow.com/questions/6481260/non-virtual-interface-design-pattern-question-in-c-c

#include <iostream>
using namespace std;

class Animal
{
public:
   void speak() const { std::cout << getSound() << std::endl; }
private:
   virtual std::string getSound() const = 0;
};

class Dog : public Animal
{
private:
   std::string getSound() const { return "Woof!"; }
};

class Cat : public Animal
{
private:
   std::string getSound() const { return "Meow!"; }
};

int main()
{
  Cat c;
  c.speak();
  return 0;
}
