//=============================================================================
//
// 

#ifndef RandomStringGenerator_H
#define RandomStringGenerator_H

#include <random>

//=============================================================================
class RandomStringGenerator {
public:

  RandomStringGenerator();

  std::vector<std::string> make_strings(
    std::size_t number_of_strings,
    std::size_t max_string_length
  );

  std::string make_string(std::size_t max_string_length);
    
private:

  std::minstd_rand0 m_generator;
};

//=============================================================================
RandomStringGenerator::RandomStringGenerator()
  // default construct m_generator, that makes this repeatable.
{
}

//=============================================================================
std::string RandomStringGenerator::make_string(
  std::size_t max_string_length
)
{
  std::string random_string;
  int length = m_generator() % max_string_length;
  for (int i = 0; i < length; ++i) {
    // get a random number in [32,126] to make a char
    int character = (m_generator() % 95) + 32;
    random_string.push_back(static_cast<char>(character));
  }
  return random_string;

}

//=============================================================================
std::vector<std::string> RandomStringGenerator::make_strings(
  std::size_t number_of_strings,
  std::size_t max_string_length
)
{
  std::vector<std::string> vector;
  for (std::size_t i = 0; i < number_of_strings; ++i) {
    vector.push_back(make_string(max_string_length));
  }
  return vector;
}

#endif
