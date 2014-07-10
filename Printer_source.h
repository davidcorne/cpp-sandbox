//=============================================================================

//=============================================================================
Printer::Printer(std::ostream& os)
  : m_os(os)
{
}

//=============================================================================
Printer::~Printer()
{
}

//=============================================================================
template <typename T, typename... Args>
void Printer::print(const T& to_print, Args... arguments)
{
  m_os << to_print;
  print(arguments...);
}

//=============================================================================
void Printer::print()
{
  m_os << std::endl;
}

//=============================================================================
template <typename... Args>
void print(Args... arguments)
{
  Printer printer(std::cout);
  printer.print(arguments...);
}

