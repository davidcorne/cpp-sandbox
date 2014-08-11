//=============================================================================
//
// 

#include <iostream>
#include <string>

//=============================================================================
#define Interface(cls, functions) \
  struct cls {                    \
    cls() {}                      \
    functions                     \
    virtual ~cls() = 0;           \
  };                              \
  cls::~cls() {}

//=============================================================================
Interface(
  IPrinter,
  virtual void print() const = 0;
);

//=============================================================================
Interface(
  IFileInterface,
  virtual void write(std::string in) = 0;
  virtual std::string read() const = 0;
);

//=============================================================================
class Printer : public IPrinter {
public:
  Printer(const IFileInterface& file)
    : m_file(file)
    {}
  
  virtual void print() const
    {
      std::cout << m_file.read() << std::endl;
    }
private:
  const IFileInterface& m_file;
};

//=============================================================================
class FileInterface : public IFileInterface {
public:

  FileInterface()
    : m_contents("")
    {}
  
  virtual void write(std::string in)
    {
      m_contents = in;
    }

  virtual std::string read() const
    {
      return m_contents;
    }

private:
  std::string m_contents;
};
//=============================================================================
int main() {
  FileInterface file;
  file.write("Write\nthis\nto\nfile\n\nend.");
  Printer printer(file);
  printer.print();
  return 0;
}
