//=============================================================================
// This is a macro which defines an enum and a conversion to string function.

#ifndef EnumConverter_H
#define EnumConverter_H

#include <cassert>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

//=============================================================================
template <typename tENUM>
class EnumConverter {
public:

  EnumConverter() {assert(!s_unsplit_string.empty());}
  
  std::string operator()(tENUM day){
    inititalise();
    return s_container->at(static_cast<size_t>(day));
  }

  tENUM operator()(std::string value){
    // find the value in the container, return it's index as an enum.
    inititalise();
    std::vector<std::string>& container = *s_container;
    auto it = std::find(begin(container), end(container), value);
    assert(it != end(container) && "Couldn't find value");
    size_t distance =  std::distance(begin(container), it);
    return static_cast<tENUM>(distance);
  }

private:

  void inititalise() {
    if (!s_container) {                                                 
      s_container.reset(new std::vector<std::string>());                
      size_t start = 0;                                                 
      size_t current = s_unsplit_string.find(", ");                       
      while (current != std::string::npos) {                            
        s_container->push_back(                                         
          std::string(s_unsplit_string, start, current - start)           
        );                                                              
        start = current + 2;                                            
        current = s_unsplit_string.find(", ", start);                     
      }                                                                 
      s_container->push_back(                                           
        std::string(s_unsplit_string, start, s_unsplit_string.length() - start)
      );                                                                
    }                                                                   
  }
  static std::unique_ptr<std::vector<std::string> > s_container;
  static std::string s_unsplit_string;
};

#define ENUM_WITH_CONVERTER(NAME, VALUES...)                            \
  enum NAME {                                                           \
    VALUES                                                              \
  };                                                                    \
  typedef EnumConverter<NAME> NAME##Converter;                          \
  template<>                                                            \
  std::string EnumConverter<NAME>::s_unsplit_string(#VALUES);           \

template <typename tENUM>
std::unique_ptr<std::vector<std::string> > EnumConverter<tENUM>::s_container(nullptr);

#endif
