//=============================================================================
//
// A test of http://accu.org/index.php/journals/1924?utm_content=buffer25009&utm_medium=social&utm_source=plus.google.com&utm_campaign=buffer

#include <cassert>
#include <iostream>
#include <string>

#include <UnitCpp.h>

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
  
  PathRemover() {}
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
  
  Writer() {};
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
  
  Reader() {};
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
void write(Writer& writer)
{
  writer.write("Hello");
  writer.close();
}

//=============================================================================
void read(Reader& reader)
{
  reader.read();
  reader.close();
}

//=============================================================================
TEST(MinimalOverheadForMultipleInterfaces, reading)
{
  FileSystem file_system;
  read(file_system.reader(Path("dummy")));
}

//=============================================================================
TEST(MinimalOverheadForMultipleInterfaces, writing)
{
  FileSystem file_system;
  write(file_system.writer(Path("dummy")));
}

//=============================================================================
TEST(MinimalOverheadForMultipleInterfaces, removing)
{
  FileSystem file_system;
  PathRemover& remover = file_system.path_remover();
  remover.remove(Path("to-delete"));
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
