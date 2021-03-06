//=============================================================================
//
// 

#include <iostream>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <UnitCpp.h>

class Employee;

//=============================================================================
class IEmployeeVisitor {
public:

  IEmployeeVisitor();
  
  virtual void visit(Employee& employee) = 0;
  
  virtual ~IEmployeeVisitor() = 0;

private:
  IEmployeeVisitor(const IEmployeeVisitor&);
  IEmployeeVisitor& operator=(const IEmployeeVisitor&);
};

//=============================================================================
class Employee {
public:
  
  Employee(std::string name, double wage)
    : m_name(name),
      m_wage(wage)
    {}

  std::string name() const
    {
      return m_name;
    }

  double wage() const
    {
      return m_wage;
    }
     
  void accept_visitor(IEmployeeVisitor& visitor)
    {
      visitor.visit(*this);
    }

private:
  std::string m_name;
  double m_wage;  
};

//=============================================================================
class EmployeeDatabase {
public:

  EmployeeDatabase() {}

  void add(Employee employee)
    {
      m_db.push_back(employee);
    }

  void accept_visitor(IEmployeeVisitor& visitor)
    {
      for (auto it = m_db.begin(); it != m_db.end(); ++it) {
        it->accept_visitor(visitor);
      }
    }
     
private:

  std::vector<Employee> m_db;
};

//=============================================================================
class EmployeePrinter : public IEmployeeVisitor {
public:

  EmployeePrinter()
    : m_to_print("")
    {}
  
  virtual void visit(Employee& employee) override;

  std::string flush();

  virtual ~EmployeePrinter() {}
  
private:
  std::string m_to_print;
};

//=============================================================================
TEST(EmployeeVisitor, employee_printer)
{
  Employee dave("Dave", 250.00);
  EmployeePrinter printer;
  dave.accept_visitor(printer);
  TEST_EQUAL(
    printer.flush(), "| Dave | 250.00 |\n",
    "Wrong string from printer."
  );
}

//=============================================================================
TEST(EmployeeVisitor, employee_database_printer)
{
  EmployeeDatabase db;
  db.add(Employee("Dave", 250.00));
  EmployeePrinter printer;
  db.accept_visitor(printer);
  TEST_EQUAL(
    printer.flush(), "| Dave | 250.00 |\n",
    "Wrong string from printer."
  );
  db.add(Employee("David", 350.00));
  db.accept_visitor(printer);
  TEST_EQUAL(
    printer.flush(), "| Dave | 250.00 |\n| David | 350.00 |\n",
    "Wrong string from printer."
  );
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
std::string EmployeePrinter::flush()
{
  std::string out(m_to_print);
  m_to_print.clear();
  return out;
}

//=============================================================================
void EmployeePrinter::visit(Employee& employee)
{
  m_to_print += "| ";
  m_to_print += employee.name();
  m_to_print += " | ";
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(2) << employee.wage();
  m_to_print += ss.str();
  m_to_print += " |";
  m_to_print += "\n";
}

IEmployeeVisitor::IEmployeeVisitor(){}
IEmployeeVisitor::~IEmployeeVisitor(){}

