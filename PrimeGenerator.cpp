//=============================================================================
//
// 

#include "Capabilities.h"
#if CAPABILITY_INITIALISER_LISTS
#include <iostream>
#include <vector>
#include <math.h>

#include <UnitCpp/Test.h>

#include "Iterator.h"

//=============================================================================
class PrimeGenerator {
public:
  typedef int BigNum;
  
  PrimeGenerator(BigNum limit);

  ~PrimeGenerator();

  Iterator<BigNum> primes() const;
  
private:

  //===========================================================================
  class PrimeIterator : public AbsIterator<BigNum> {
  public:

    PrimeIterator(BigNum limit);

    virtual ~PrimeIterator();

    virtual std::unique_ptr<AbsIterator<BigNum> > clone() const override;
  
    virtual bool operator++() override;

    virtual BigNum& operator()() override;

    virtual const BigNum& operator()() const override;
    
  private:

    bool prime(BigNum number) const;
    
    const BigNum m_limit;
    BigNum m_current;
    
  };

  friend class utest_PrimeGenerator;

  BigNum m_limit;
};

//=============================================================================
TEST(PrimeGenerator, 100)
{
  PrimeGenerator generator(100);
  Iterator<PrimeGenerator::BigNum> prime_iter = generator.primes();
  int count = 0;
  std::vector<PrimeGenerator::BigNum> primes;
  while (++prime_iter) {
    ++count;
    primes.push_back(prime_iter());
  }
  TEST_EQUAL(count, 25, "Should be 25 primes under 100.");
  std::vector<PrimeGenerator::BigNum> reference_primes =
    {
      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
      71,73, 79, 83, 89, 97
    };
  TEST_EQUAL(primes, reference_primes, "Incorrect primes under 100.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
PrimeGenerator::PrimeGenerator(PrimeGenerator::BigNum limit)
  : m_limit(limit)
{

}


//=============================================================================
PrimeGenerator::~PrimeGenerator()
{

}


//=============================================================================
Iterator<PrimeGenerator::BigNum> PrimeGenerator::primes() const
{
  Iterator<BigNum> iter(std::unique_ptr<PrimeIterator>(new PrimeIterator(m_limit)));
  return iter;
}

//=============================================================================
PrimeGenerator::PrimeIterator::PrimeIterator(PrimeGenerator::BigNum limit)
  : m_limit(limit),
    m_current(1)
{
}

//=============================================================================
PrimeGenerator::PrimeIterator::~PrimeIterator()
{
}

//=============================================================================
std::unique_ptr<AbsIterator<PrimeGenerator::BigNum> > PrimeGenerator::PrimeIterator::clone() const
{
  PrimeIterator* iter = new PrimeIterator(m_limit);
  iter->m_current = m_current;

  std::unique_ptr<AbsIterator<PrimeGenerator::BigNum> > ptr(iter);
  return ptr;
}
  
//=============================================================================
bool PrimeGenerator::PrimeIterator::operator++()
{
  ++m_current;
  while (!prime(m_current)) {
    ++m_current;
  }
  
  return m_current < m_limit;
}

//=============================================================================
PrimeGenerator::BigNum& PrimeGenerator::PrimeIterator::operator()()
{
  return m_current;
}

//=============================================================================
const PrimeGenerator::BigNum& PrimeGenerator::PrimeIterator::operator()() const
{
  return m_current;
}

//=============================================================================
bool PrimeGenerator::PrimeIterator::prime(BigNum number) const
{
  if (number % 2 == 0) {
    return number == 2;
  }
  for (BigNum i = 3; i <= sqrt(number); i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

#else
UNSUPPORTED_FEATURE_MAIN;
#endif

