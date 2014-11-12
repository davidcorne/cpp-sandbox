//=============================================================================

#include "Capabilities.h"
#if CAPABILITY_DEFAULTED_FUNCTIONS

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
namespace dgc {
  // specialise to_string for Shoe::Grading.
  template <>
  std::string to_string(const Shoe::Grading& grading) {
    static const std::map<Shoe::Grading, std::string> converter = {
      {Shoe::EU_GRADING, "EU"},
      {Shoe::UK_GRADING, "UK"},
      {Shoe::US_GRADING, "US"}
    };
    return converter.at(grading);
  }
}

//=============================================================================
std::string Shoe::repr() const
{

  std::string result("");
  result += dgc::to_string(m_grading) + ":" + dgc::to_string(m_size);
  return result;
}
  
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_DEFAULTED_FUNCTIONS)
#endif
