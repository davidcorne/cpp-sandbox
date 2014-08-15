//=============================================================================

#include <iostream>
#include <string>
#include <map>

//=============================================================================
class IPrintable {
public:

  IPrintable();
  
  virtual ~IPrintable() = 0;

private:

  virtual std::string repr() const = 0;
  
  friend std::ostream& operator<<(std::ostream& os, const IPrintable& printable);
};

//=============================================================================
std::ostream& operator<<(std::ostream& os, const IPrintable& printable);

//=============================================================================
class Shoe : public IPrintable {
public:
  enum Grading {
    EU_GRADING,
    UK_GRADING,
    US_GRADING
  };
  
  Shoe(Grading grading, double size);

  virtual ~Shoe();
  
private:

  std::string repr() const override;

  Grading m_grading;
  double m_size;
};

//=============================================================================
int main()
{
  Shoe eu_shoe(Shoe::EU_GRADING, 42);
  Shoe uk_shoe(Shoe::UK_GRADING, 9);
  Shoe us_shoe(Shoe::US_GRADING, 8);
  std::cout << eu_shoe << " " << uk_shoe << " " << us_shoe << std::endl;
}

//----- IPrintable

//=============================================================================
IPrintable::IPrintable() = default;
IPrintable::~IPrintable() = default;

//=============================================================================
std::ostream& operator<<(std::ostream& os, const IPrintable& printable)
{
  os << printable.repr();
  return os;
}

//----- Shoe

#include "to_string.h"

//=============================================================================
Shoe::Shoe(Shoe::Grading grading, double size)
  : m_grading(grading),
    m_size(size)
{
}

//=============================================================================
Shoe::~Shoe() = default;

//=============================================================================
std::string Shoe::repr() const
{
  std::map<Grading, std::string> converter = {
    {EU_GRADING, "EU"},
    {UK_GRADING, "UK"},
    {US_GRADING, "US"}
  };

  std::string result("");
  result += converter.at(m_grading) + ":" + to_string(m_size);
  return result;
}
  
