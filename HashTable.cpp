//=============================================================================
// Mainly based on a version of
// http://www.algolist.net/Data_structures/Hash_table/Simple_example

#include <iostream>
#include <UnitCpp.h>

#include "Iterator.h"

//=============================================================================
template <typename tKEY, typename tVALUE>
class HashEntry {
public:
  
  HashEntry(tKEY key, tVALUE value);
  ~HashEntry();
  
  tKEY key() const;
  
  tVALUE value() const;
    
private:
  
  tKEY m_key;
  tVALUE m_value;
};

//=============================================================================
template <typename tKEY, typename tVALUE>
class HashMap {
public:

  HashMap();

  ~HashMap();

  tVALUE get(tKEY key) const;

  void put(tKEY key, tVALUE value);

  int size() const;

  Iterator<HashEntry<tKEY, tVALUE>> iterator();
  
private:

  int offset(tKEY key) const;
  // Get the offset to put the key in.

  void resize(int new_size);
  // Re-size the array to the new_size
  // Precondition: new_size > m_current_size;

  template <typename tOTHER_KEY, typename tOTHER_VALUE>
  friend class HashMapIterator;
  
  HashMap(const HashMap<tKEY, tVALUE>&);
  HashMap<tKEY, tVALUE>& operator=(const HashMap<tKEY, tVALUE>&);

  int m_table_size;
  int m_current_size;
  HashEntry<tKEY, tVALUE>** m_table;
};

//=============================================================================
template <typename tKEY, typename tVALUE>
class HashMapIterator : public AbsIterator<HashEntry<tKEY, tVALUE>> {
public:

  HashMapIterator(const HashMap<tKEY, tVALUE>& map);

  HashMapIterator(const HashMapIterator<tKEY, tVALUE>& iter);
  HashMapIterator& operator=(const HashMapIterator<tKEY, tVALUE>& iter);

  virtual std::unique_ptr<AbsIterator<HashEntry<tKEY, tVALUE> > > clone() const override;
  
  virtual bool operator++() override;

  virtual HashEntry<tKEY, tVALUE>& operator()() override;

  virtual const HashEntry<tKEY, tVALUE>& operator()() const override;

  virtual ~HashMapIterator();
  
private:

  const HashMap<tKEY, tVALUE>* m_map;
  int m_index;
};

//----- Tests
//=============================================================================
TEST(HashMap, constructor)
{
  HashMap<int, int> map;
}

//=============================================================================
TEST(HashMap, size)
{
  HashMap<int, int> map;
  TEST_EQUAL(map.size(), 0);
  map.put(3, 1);
  TEST_EQUAL(map.size(), 1);
}

//=============================================================================
TEST(HashMap, put)
{
  HashMap<int, int> map;
  map.put(1, 3);
  TEST_EQUAL(map.get(1), 3);
}

//=============================================================================
TEST(HashMap, dynamic)
{
  HashMap<int, int> map;
  for (int i = 0; i < 150; ++i) {
    map.put(i, 150 - i);
  }
  TEST_EQUAL(map.size(), 150);
  stop_printing();
  for (int i = 0; i < 150; ++i) {
    TEST_EQUAL(map.get(i), 150 - i);
  }
  restart_printing();
}

//=============================================================================
TEST(HashMap, collisions)
{
  HashMap<int, int> map;
  int start = 5;
  for (int i = start; i < start + (128 * 128); i += 128) {
    map.put(i, 0);
  }
}

//=============================================================================
TEST(HashMapIterator, constructor)
{
  HashMap<int, int> map;
  HashMapIterator<int, int> iterator(map);
}

//=============================================================================
TEST(HashMapIterator, iterating)
{
  HashMap<int, int> map;
  map.put(5, -10);
  map.put(1, 0);
  HashMapIterator<int, int> iterator(map);
  bool ok = false;
  ok = ++iterator;
  TEST_TRUE(ok);
  ok = ++iterator;
  TEST_TRUE(ok);
  ok = ++iterator;
  TEST_FALSE(ok);
}


//----- Implementations
//----- HashMap
//=============================================================================
template <typename tKEY, typename tVALUE>
HashMap<tKEY, tVALUE>::HashMap()
  : m_table_size(128),
    m_current_size(0),
    m_table(nullptr)
{
  m_table = new HashEntry<tKEY, tVALUE>*[m_table_size];
  for (int i = 0; i < m_table_size; ++i) {
    m_table[i] = nullptr;
  }
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashMap<tKEY, tVALUE>::~HashMap()
{
  for (int i = 0; i < m_table_size; ++i) {
    if (m_table[i]) {
      delete m_table[i];
    }
  }
  delete[] m_table;
  m_table = 0;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
int HashMap<tKEY, tVALUE>::offset(tKEY key) const
{
  int hash = (key % m_table_size);
  int original_hash = hash;
  // the hash is where it should go.
  while (m_table[hash] && m_table[hash]->key() != key) {
    // There's been a collision!
    hash = (hash + 1) % m_table_size;
    assert((hash != original_hash) && "Hash has gone round again.");
  }
  return hash;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
tVALUE HashMap<tKEY, tVALUE>::get(tKEY key) const
{
  tVALUE value = -1;
  int hash = offset(key);
  if (m_table[hash]) {
    value = m_table[hash]->value();
  }
  return value;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
void HashMap<tKEY, tVALUE>::put(tKEY key, tVALUE value)
{
  if (m_current_size > (m_table_size / 2)) {
    resize(m_table_size * 2);
  }
  int hash = offset(key);
  if (m_table[hash]) {
    delete m_table[hash];
  } else {
    ++m_current_size;
  }
  m_table[hash] = new HashEntry<tKEY, tVALUE>(key, value);
}

//=============================================================================
template <typename tKEY, typename tVALUE>
int HashMap<tKEY, tVALUE>::size() const
{
  return m_current_size;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
void HashMap<tKEY, tVALUE>::resize(int new_size)
{
  assert((new_size > m_table_size) && "Incorrect size passed to resize().");
  HashEntry<tKEY, tVALUE>** larger_array = new HashEntry<tKEY, tVALUE>*[new_size];
  for (int i = 0; i < m_table_size; ++i) {
    larger_array[i] = m_table[i];
  }
  for (int i = m_table_size; i < new_size; ++i) {
    larger_array[i] = nullptr;
  }
  m_table_size = new_size;
  delete[] m_table;
  m_table = larger_array;
}

//----- HashEntry
//=============================================================================
template <typename tKEY, typename tVALUE>
HashEntry<tKEY, tVALUE>::HashEntry(tKEY key, tVALUE value)
  : m_key(key),
    m_value(value)
{
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashEntry<tKEY, tVALUE>::~HashEntry()
{
}

//=============================================================================
template <typename tKEY, typename tVALUE>
tKEY HashEntry<tKEY, tVALUE>::key() const
{
  return m_key;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
tVALUE HashEntry<tKEY, tVALUE>::value() const
{
  return m_value;
}

//----- HashMapIterator
//=============================================================================
template <typename tKEY, typename tVALUE>
HashMapIterator<tKEY, tVALUE>::HashMapIterator(const HashMap<tKEY, tVALUE>& map)
  : m_map(&map),
    m_index(-1)
{
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashMapIterator<tKEY, tVALUE>::HashMapIterator(const HashMapIterator<tKEY, tVALUE>& other)
  :  m_map(other.m_map),
     m_index(other.m_index)
{
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashMapIterator<tKEY, tVALUE>& HashMapIterator<tKEY, tVALUE>::operator=(const HashMapIterator<tKEY, tVALUE>& other)
{
  m_map = other.m_map;
  m_index = other.m_index;
  return *this;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashMapIterator<tKEY, tVALUE>::~HashMapIterator()
{
}

//=============================================================================
template <typename tKEY, typename tVALUE>
std::unique_ptr<AbsIterator<HashEntry<tKEY, tVALUE>> > HashMapIterator<tKEY, tVALUE>::clone() const
{
  std::unique_ptr<AbsIterator<HashEntry<tKEY, tVALUE>> > other(
    new HashMapIterator<tKEY, tVALUE>(*this)
  );
  return other;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
bool HashMapIterator<tKEY, tVALUE>::operator++()
{
  while (m_index < m_map->m_table_size) {
    ++m_index;
    if (m_map->m_table[m_index]) {
      break;
    }
  }
  return m_index < m_map->m_table_size;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
HashEntry<tKEY, tVALUE>& HashMapIterator<tKEY, tVALUE>::operator()()
{
  HashEntry<tKEY, tVALUE>* entry = m_map->m_table[m_index];
  assert(entry && "Null entry.");
  return *entry;
}

//=============================================================================
template <typename tKEY, typename tVALUE>
const HashEntry<tKEY, tVALUE>& HashMapIterator<tKEY, tVALUE>::operator()() const
{
  HashEntry<tKEY, tVALUE>* entry = m_map->m_table[m_index];
  assert(entry && "Null entry.");
  return *entry;
}

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(
    argc,
    argv
  );
}

