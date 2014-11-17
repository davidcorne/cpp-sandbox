//=============================================================================
// Mainly based on a version of
// http://www.algolist.net/Data_structures/Hash_table/Simple_example

typedef int Key;
typedef int Value;

#include <iostream>
#include <UnitCpp/Test.h>

#include "Iterator.h"

//=============================================================================
class HashEntry {
public:
  
  HashEntry(Key key, Value value);
  ~HashEntry();
  
  Key key() const;
  
  Value value() const;
    
private:
  
  Key m_key;
  Value m_value;
};

//=============================================================================
class HashMap {
public:

  HashMap();

  ~HashMap();

  Value get(Key key) const;

  void put(Key key, Value value);

  int size() const;

  Iterator<HashEntry> iterator();
  
private:

  int offset(Key key) const;
  // Get the offset to put the key in.

  void resize(int new_size);
  // Re-size the array to the new_size
  // Precondition: new_size > m_current_size;
  
  friend class HashMapIterator;
  
  HashMap(const HashMap&);
  HashMap& operator=(const HashMap&);

  int m_table_size;
  int m_current_size;
  HashEntry** m_table;
};

//=============================================================================
class HashMapIterator : public AbsIterator<HashEntry> {
public:

  HashMapIterator(const HashMap& map);

  HashMapIterator(const HashMapIterator& iter);
  HashMapIterator& operator=(const HashMapIterator& iter);

  virtual std::unique_ptr<AbsIterator<HashEntry> > clone() const override;
  
  virtual bool operator++() override;

  virtual HashEntry& operator()() override;

  virtual const HashEntry& operator()() const override;

  virtual ~HashMapIterator();
  
private:

  const HashMap* m_map;
  int m_index;
};

//----- Tests
//=============================================================================
TEST(HashMap, constructor)
{
  HashMap map;
}

//=============================================================================
TEST(HashMap, size)
{
  HashMap map;
  TEST_EQUAL(map.size(), 0);
  map.put(3, 1);
  TEST_EQUAL(map.size(), 1);
}

//=============================================================================
TEST(HashMap, put)
{
  HashMap map;
  map.put(1, 3);
  TEST_EQUAL(map.get(1), 3);
}

//=============================================================================
TEST(HashMap, dynamic)
{
  HashMap map;
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
  HashMap map;
  int start = 5;
  for (int i = start; i < start + (128 * 128); i += 128) {
    map.put(i, 0);
  }
}

//=============================================================================
TEST(HashMapIterator, constructor)
{
  HashMap map;
  HashMapIterator iterator(map);
}

//=============================================================================
TEST(HashMapIterator, iterating)
{
  HashMap map;
  map.put(5, -10);
  map.put(1, 0);
  HashMapIterator iterator(map);
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
HashMap::HashMap()
  : m_table_size(128),
    m_current_size(0),
    m_table(nullptr)
{
  m_table = new HashEntry*[m_table_size];
  for (int i = 0; i < m_table_size; ++i) {
    m_table[i] = nullptr;
  }
}

//=============================================================================
HashMap::~HashMap()
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
int HashMap::offset(Key key) const
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
Value HashMap::get(Key key) const
{
  Value value = -1;
  int hash = offset(key);
  if (m_table[hash]) {
    value = m_table[hash]->value();
  }
  return value;
}

//=============================================================================
void HashMap::put(Key key, Value value)
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
  m_table[hash] = new HashEntry(key, value);
}

//=============================================================================
int HashMap::size() const
{
  return m_current_size;
}

//=============================================================================
void HashMap::resize(int new_size)
{
  assert((new_size > m_table_size) && "Incorrect size passed to resize().");
  HashEntry** larger_array = new HashEntry*[new_size];
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
HashEntry::HashEntry(Key key, Value value)
  : m_key(key),
    m_value(value)
{
}

//=============================================================================
HashEntry::~HashEntry()
{
}

//=============================================================================
Key HashEntry::key() const
{
  return m_key;
}

//=============================================================================
Value HashEntry::value() const
{
  return m_value;
}

//----- HashMapIterator
//=============================================================================
HashMapIterator::HashMapIterator(const HashMap& map)
  : m_map(&map),
    m_index(-1)
{
}

//=============================================================================
HashMapIterator::HashMapIterator(const HashMapIterator& other)
  :  m_map(other.m_map),
     m_index(other.m_index)
{
}

//=============================================================================
HashMapIterator& HashMapIterator::operator=(const HashMapIterator& other)
{
  m_map = other.m_map;
  m_index = other.m_index;
  return *this;
}

//=============================================================================
HashMapIterator::~HashMapIterator()
{
}

//=============================================================================
std::unique_ptr<AbsIterator<HashEntry> > HashMapIterator::clone() const
{
  std::unique_ptr<AbsIterator<HashEntry> > other(
    new HashMapIterator(*this)
  );
  return other;
}

//=============================================================================
bool HashMapIterator::operator++()
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
HashEntry& HashMapIterator::operator()()
{
  HashEntry* entry = m_map->m_table[m_index];
  assert(entry && "Null entry.");
  return *entry;
}

//=============================================================================
const HashEntry& HashMapIterator::operator()() const
{
  HashEntry* entry = m_map->m_table[m_index];
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

