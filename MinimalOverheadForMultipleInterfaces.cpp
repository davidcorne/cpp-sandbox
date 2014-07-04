//=============================================================================
//
// A test of http://accu.org/index.php/journals/1924?utm_content=buffer25009&utm_medium=social&utm_source=plus.google.com&utm_campaign=buffer

#include <assert.h>
#include <iostream>
#include <string>

#include "UnitTest.h"
#include "Path.h"

//=============================================================================
class FileSystemImplementation {
protected:

  FileSystemImplementation()
    : m_path(""),
      m_mode("")
    {}
  
  void remove(Path path) {
    std::cout << "\"" << path << "\" removed." << std::endl;
  }
  
  void open_read(Path path) {
    m_path = path;
    m_mode = "R";
  }
  
  void open_write(Path path) {
    m_path = path;
    m_mode = "W";
  }
  
  void read() const {
    assert(m_mode == "R");
    std::cout << "Read: " << m_path << std::endl;
  }

  void write(std::string contents) {
    assert(m_mode == "W");
    std::cout << "Write: \"" << contents << "\" to " << m_path << std::endl;
  }

  void close() {
    std::cout << "Close: " << m_path << std::endl;
  }

private:
  Path m_path;
  std::string m_mode;
};

//=============================================================================
class PathRemover : private FileSystemImplementation {
public:
  
  using FileSystemImplementation::remove;

protected:
  
  PathRemover() = default;
};

//=============================================================================
class Writer : private FileSystemImplementation {
public:

  using FileSystemImplementation::write;
  using FileSystemImplementation::close;

protected:
  
  void open(Path path) {
    open_write(path);
  }
  
  Writer() = default;
};

//=============================================================================
class Reader : private FileSystemImplementation {
public:

  using FileSystemImplementation::read;
  using FileSystemImplementation::close;
  
protected:

  void open(Path path) {
    open_read(path);
  }
  
  Reader() = default;
};

//=============================================================================
class FileSystem :
  private Reader,
  private Writer,
  private PathRemover
{
public:

  Reader& reader(Path path) {
    Reader::open(path);
    return *this;
  }

  Writer& writer(Path path) {
    Writer::open(path);
    return *this;
  }

  PathRemover& path_remover() {
    return *this;
  }
};

//=============================================================================
class utest_MinimalOverheadForMultipleInterfaces : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_reading();
    test_writing();
    test_removing();
  }

private:
  void write(Writer& writer);
  void read(Reader& reader);
  
  void test_writing();
  void test_reading();
  void test_removing();

};

//=============================================================================
void utest_MinimalOverheadForMultipleInterfaces::write(Writer& writer)
{
  writer.write("Hello");
  writer.close();
}

//=============================================================================
void utest_MinimalOverheadForMultipleInterfaces::read(Reader& reader)
{
  reader.read();
  reader.close();
}

//=============================================================================
void utest_MinimalOverheadForMultipleInterfaces::test_reading()
{
  print(DGC_CURRENT_FUNCTION);
  FileSystem file_system;
  read(file_system.reader(Path("dummy")));
}

//=============================================================================
void utest_MinimalOverheadForMultipleInterfaces::test_writing()
{
  print(DGC_CURRENT_FUNCTION);
  FileSystem file_system;
  write(file_system.writer(Path("dummy")));
}

//=============================================================================
void utest_MinimalOverheadForMultipleInterfaces::test_removing()
{
  print(DGC_CURRENT_FUNCTION);
  FileSystem file_system;
  PathRemover& remover = file_system.path_remover();
  remover.remove(Path("to-delete"));
}

//=============================================================================
int main() {
  utest_MinimalOverheadForMultipleInterfaces test;
  test.run_tests();
  return 0;
}
