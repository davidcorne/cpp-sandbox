//=============================================================================
//
// 

#include <iostream>
#include <sstream>
#include <string>

#include <UnitCpp/Test.h>

//=============================================================================
class IEmployeeExporter {
public:

  virtual void set_name(std::string name) = 0;
  virtual void set_wage(double wage) = 0;
  virtual void set_id(std::string id) = 0;
  
  virtual ~IEmployeeExporter() = 0;
  
};

IEmployeeExporter::~IEmployeeExporter() {}

//=============================================================================
class Employee {
public:

  Employee(std::string name, double wage, std::string id)
    : m_name(name),
      m_wage(wage),
      m_id(id)
    {}
  
  void output(IEmployeeExporter& exporter) const
    {
      exporter.set_name(m_name);
      exporter.set_wage(m_wage);
      exporter.set_id(m_id);
    }
      
private:
  
  std::string m_name;
  double m_wage;
  std::string m_id;
};

//=============================================================================
class EmployeeExporterImpl : public IEmployeeExporter {
  
  virtual void set_name(std::string name) override
    {
      m_name = name;
    }
  
  virtual void set_wage(double wage) override
    {
      m_wage = wage;
    }

  virtual void set_id(std::string id) override
    {
      m_id = id;
    }

protected:
  
  std::string m_name;
  double m_wage;
  std::string m_id;  
};

//=============================================================================
class EmployeeHTMLExporter : public EmployeeExporterImpl {
public:

  std::string out() const
    {
      std::stringstream stream;
      stream
        << "<table border=\"0\">\n"
        << "  <tr><td>Name:</td><td>"
        << m_name
        << "</td></tr>\n"
        << "  <tr><td>Wage:</td><td>"
        << m_wage
        << "</td></tr>\n"
        << "  <tr><td>ID:</td><td>"
        << m_id
        << "</td></tr>\n"
        << "</table>";
      return stream.str();
    }
};

//=============================================================================
class EmployeeJSONExporter : public EmployeeExporterImpl {
public:

  std::string out() const
    {
      std::stringstream stream;
      stream
        << "{\n"
        << "\"name\": \""
        << m_name
        << "\",\n"
        << "\"wage\": "
        << m_wage
        << ",\n"
        << "\"id\": \""
        << m_id
        << "\",\n"
        << "}";
      return stream.str();
    }
};

//=============================================================================
TEST(UIBuilder, html)
{
  Employee fred("Fred", 40000, "01fg6");
  EmployeeHTMLExporter exporter;
  fred.output(exporter);
  std::string result("<table border=\"0\">\n"
                "  <tr><td>Name:</td><td>Fred</td></tr>\n"
                "  <tr><td>Wage:</td><td>40000</td></tr>\n"
                "  <tr><td>ID:</td><td>01fg6</td></tr>\n"
                "</table>"
  );
  TEST_EQUAL(result, exporter.out(), "Wrong html output.");  
}

//=============================================================================
TEST(UIBuilder, json)
{
  Employee fred("Fred", 40000, "01fg6");
  EmployeeJSONExporter exporter;
  fred.output(exporter);
  std::string expected_result("{\n"
                "\"name\": \"Fred\",\n"
                "\"wage\": 40000,\n"
                "\"id\": \"01fg6\",\n"
                "}"
  );
  TEST_EQUAL(expected_result, exporter.out(), "Wrong json output.");  
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

