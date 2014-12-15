//=============================================================================

#ifndef Printer_H
#define Printer_H

#include "Capabilities.h"
#if CAPABILITY_VARIADIC_TEMPLATES
#include <iostream>

//=============================================================================
class Printer {
public:

  explicit Printer(std::ostream& os = std::cout);

  ~Printer();
  
  template <typename T, typename... Args>
  void print(const T& to_print, Args... arguments);

  void print();

private:

  Printer(const Printer&);
  Printer& operator=(const Printer&);
  // Copying prohibited.
  
  std::ostream& m_os;
};

//=============================================================================
template <typename... Args>
void print(Args... arguments);

#include "Printer_source.h"
#else
#error "Variadic templates not supported."
#endif // CAPABILITY_VARIADIC_TEMPLATES
#endif // Printer_H
