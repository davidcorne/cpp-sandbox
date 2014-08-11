#include <iostream>
#include <stdexcept>

class Bank {
public:

  Bank(int money)
    : m_money(money),
      m_thing(false),
      another_thing(-5.3234)
    {}
  
  void show_balance() {
    std::cout << "Your balance is: " << m_money << std::endl;
  }
  
private:
  int m_money;
  bool m_thing;
  double another_thing;
};

void printf(const char *s)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << *s++;
    }
}
 
int main() {
  Bank my_bank(14);
  // printf("hi");
  // <nnn> change<Bank, int, double, bool>(my_bank, 2000);
  
  return 0;
}
