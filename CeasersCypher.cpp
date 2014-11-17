//=============================================================================

#include "Capabilities.h"
#if CAPABILITY_RANGE_BASE_FOR
#include <UnitCpp/Test.h>

//=============================================================================
class Cyper {
public:

  Cyper();
  
  virtual ~Cyper() = 0;
  
  virtual std::string encrypt(std::string in) = 0;

  virtual std::string decrypt(std::string in) = 0;
};

//=============================================================================
class CeaserCypher : public Cyper {
public:

  CeaserCypher();
  
  virtual ~CeaserCypher();

  virtual std::string encrypt(std::string in) override;

  virtual std::string decrypt(std::string in) override;
};  

//=============================================================================
TEST(Cyper, encrypt)
{
  CeaserCypher cypher;
  std::string to_encrypt("afooz");
  std::string encrypted = cypher.encrypt(to_encrypt);
  TEST_NOT_EQUAL(to_encrypt, encrypted);
  std::string decrypted = cypher.decrypt(encrypted);
  TEST_EQUAL(to_encrypt, decrypted);
}

//=============================================================================
Cyper::Cyper() {}
Cyper::~Cyper() {}

//=============================================================================
CeaserCypher::CeaserCypher()
  : Cyper()
{
}

//=============================================================================
CeaserCypher::~CeaserCypher() {}

//=============================================================================
std::string CeaserCypher::encrypt(std::string to_encrypt)
{
  for (char& c: to_encrypt) {
    c += 3;
  }
  return to_encrypt;
}

//=============================================================================
std::string CeaserCypher::decrypt(std::string to_decrypt)
{
  for (char& c: to_decrypt) {
    c -= 3;
  }
  return to_decrypt;
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_RANGE_BASE_FOR);
#endif
