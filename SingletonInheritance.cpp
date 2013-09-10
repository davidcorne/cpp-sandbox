//
// 

#include <iostream>
#include <assert.h>

using namespace std;

//=============================================================================
template <class T>
class Singleton {
public:

  static const T& get();
  static T& get_modifiable();
  // Get the singleton object

  virtual ~Singleton() = 0;
  
protected:

  Singleton();

  Singleton(const Singleton&);
  Singleton& operator=(const Singleton&);
  // uncopyable
  
private:

  static T* m_instance;
};

//=============================================================================
template <class T>
T* Singleton<T>::m_instance = 0;

//=============================================================================
template <class T>
const T& Singleton<T>::get()
{
  if (!m_instance) {
    m_instance = new T;
  }
  return *m_instance;
}

//=============================================================================
template <class T>
T& Singleton<T>::get_modifiable()
{
  const T& ref = get();
  return const_cast<T&>(ref);
}

//=============================================================================
template <class T>
Singleton<T>::Singleton()
{
}

//=============================================================================
template <class T>
Singleton<T>::~Singleton()
{
  if (m_instance) {
    delete m_instance;
  }
  m_instance = 0;
}

//=============================================================================
class Logger : public Singleton<Logger> {
public:

  void log(string s) const;
  
  virtual ~Logger();
  
protected:
  friend class Singleton<Logger>;
  Logger();
};

//=============================================================================
class Data : public Singleton<Data> {
public:

  int data() const {
    return 42;
  }

  virtual ~Data();

protected:

  friend class Singleton<Data>;
  Data();
};

//=============================================================================
void Logger::log(string s) const
{
  cout << s.c_str() << endl;
}

//=============================================================================
Logger::Logger(){}

//=============================================================================
Logger::~Logger(){}

//=============================================================================
Data::Data(){}

//=============================================================================
Data::~Data(){}

//=============================================================================
int main() {
  const Logger& l = Logger::get();
  l.log("Hey");
  Logger& n = Logger::get_modifiable();
  assert(&l == &n);

  const Logger& new_way = Singleton<Logger>::get();
  assert(&new_way == &n);

  const Data& d = Data::get();
  assert(d.data() == 42);
  assert(static_cast<const void*>(&d) != static_cast<const void*>(&l));
  cout << &n << " " << &l << " " << &d << endl;
  return 0;
}
