//=============================================================================

#ifndef Printer_H
#define Printer_H

#include <iostream>

//=============================================================================
class Printer {
public:

  explicit Printer(std::ostream& os = std::cout);

  ~Printer();
  
  template <typename T, typename... Args>
  void print(const T& to_print, Args... arguments);

private:

  void print();

  std::ostream& m_os;
};

#include "Printer_source.h"
#endif
