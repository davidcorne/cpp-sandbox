#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

//=============================================================================
class BankData {
public:

  BankData(std::string name, double passcode);

  ~BankData();

  std::string name() const;
  
private:

  std::string m_name;
  double m_passcode;  
};

//=============================================================================
class Bank {
public:

  Bank();
  ~Bank();

  void add_data(BankData data);

  BankData search_user(std::string name) const;

  std::vector<BankData>::const_iterator begin() const;
  std::vector<BankData>::const_iterator end() const;
  
private:

  std::vector<BankData> m_data;
  
};

// HAXORS!

//=============================================================================
namespace hak {

  struct HackData {
    std::string name;
    double passcode;
  };

  void hack(const Bank& bank);
}

//=============================================================================
int main()
{
  Bank bank;
  bank.add_data(BankData("Dave", 1234));
  bank.add_data(BankData("Me", 1337));
  // now hack it!
  hak::hack(bank);
  return 0;
}

//----- Bank.

//=============================================================================
Bank::Bank() {}
Bank::~Bank() {}

//=============================================================================
void Bank::add_data(BankData data)
{
  m_data.push_back(data);
}

//=============================================================================
BankData Bank::search_user(std::string name) const
{
  auto it = std::find_if(
    std::begin(m_data),
    std::end(m_data),
    [name](BankData data) -> bool {return data.name() == name;}
  );
  return *it;
}

//=============================================================================
std::vector<BankData>::const_iterator Bank::begin() const
{
  return std::begin(m_data);
}

//=============================================================================
std::vector<BankData>::const_iterator Bank::end() const
{
  return std::end(m_data);
}

//----- BankData.

//=============================================================================
BankData::BankData(std::string name, double passcode)
  : m_name(name),
    m_passcode(passcode)
{
}

//=============================================================================
BankData::~BankData()
{
}

//=============================================================================
std::string BankData::name() const
{
  return m_name;
}

//----- hak

//=============================================================================
namespace hak {

  //===========================================================================
  void hack(const Bank& bank) {
    for (auto data: bank) {
      HackData* hack_data = reinterpret_cast<HackData*>(&data);
      assert(hack_data && "Hack data is not valid.");
      std::cout << hack_data->name << ":" << hack_data->passcode << std::endl;
    }
  }
}
