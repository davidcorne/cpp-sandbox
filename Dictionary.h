//=============================================================================
// The aim of this is to keep a python like dictionary, it will use strings
// for keys, but can store any copyable object.


#ifndef Dictionary_H
#define Dictionary_H

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <map>

//=============================================================================
class Dictionary {
public:

  Dictionary();
  ~Dictionary();

  template <typename T>
  void set_item(std::string key, const T& t);
  // If an item by key exists, change the value. Otherwise add a new item.
  
  template <typename T>
  const T& item(std::string key) const;
  // Get the item by key.
  // Precondition: member<T>(key)

  template <typename T>
  bool member(std::string key) const;
  // Does key have an element of type T in the dictionary?
  
private:

  std::map<std::string, std::shared_ptr<void> > m_dict;
};

//=============================================================================
Dictionary::Dictionary()
{
}

//=============================================================================
Dictionary::~Dictionary()
{
}

//=============================================================================
template <typename T>
void Dictionary::set_item(std::string key, const T& t)
{
  if (member<T>(key)) {
    *(std::static_pointer_cast<T>(m_dict[key])) = t;
  } else {
    m_dict[key] = std::make_shared<T>(t);
  }
}

//=============================================================================
template <typename T>
bool Dictionary::member(std::string key) const
{
  auto it = m_dict.find(key);
  if (it != std::end(m_dict)) {
    assert(std::static_pointer_cast<T>(it->second) && "Found item wrong type.");
  }
  return it != std::end(m_dict);
}

template <typename T>
const T& Dictionary::item(std::string key) const
{
  assert(member<T>(key) && "Key should be in the Dictionary.");
  return *(std::static_pointer_cast<T>(m_dict.at(key)));
}

#endif
