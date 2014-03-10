//=============================================================================
//
// 

#include <iostream>
#include <sstream>
#include <string>

#include "UnitTest.h"
#include "compiler_guards.h"

using namespace std;

#if CPP_ELEVEN_SUPPORTED

//=============================================================================
class IEmployeeExporter {
public:

  virtual void set_name(string name) = 0;
  virtual void set_wage(double wage) = 0;
  virtual void set_id(string id) = 0;
  
  virtual ~IEmployeeExporter() = 0;
  
};

IEmployeeExporter::~IEmployeeExporter() {}

//=============================================================================
class Employee {
public:

  Employee(string name, double wage, string id)
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
  friend class utest_UIBuilder;
  
  string m_name;
  double m_wage;
  string m_id;
};

//=============================================================================
class EmployeeExporterImpl : public IEmployeeExporter {
  
  virtual void set_name(string name) override
    {
      m_name = name;
    }
  
  virtual void set_wage(double wage) override
    {
      m_wage = wage;
    }

  virtual void set_id(string id) override
    {
      m_id = id;
    }

protected:
  
  string m_name;
  double m_wage;
  string m_id;  
};

//=============================================================================
class EmployeeHTMLExporter : public EmployeeExporterImpl {
public:

  string out() const
    {
      stringstream stream;
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

  string out() const
    {
      stringstream stream;
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
class utest_UIBuilder : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_html_output();
    test_json_output();
  }

private:

  void test_html_output();
  void test_json_output();

};

//=============================================================================
void utest_UIBuilder::test_html_output()
{
  print(DGC_CURRENT_FUNCTION);
  Employee fred("Fred", 40000, "01fg6");
  EmployeeHTMLExporter exporter;
  fred.output(exporter);
  string result("<table border=\"0\">\n"
                "  <tr><td>Name:</td><td>Fred</td></tr>\n"
                "  <tr><td>Wage:</td><td>40000</td></tr>\n"
                "  <tr><td>ID:</td><td>01fg6</td></tr>\n"
                "</table>"
  );
  test(result == exporter.out(), "Wrong html output.");  
}

//=============================================================================
void utest_UIBuilder::test_json_output()
{
  print(DGC_CURRENT_FUNCTION);
  Employee fred("Fred", 40000, "01fg6");
  EmployeeJSONExporter exporter;
  fred.output(exporter);
  string expected_result("{\n"
                "\"name\": \"Fred\",\n"
                "\"wage\": 40000,\n"
                "\"id\": \"01fg6\",\n"
                "}"
  );
  test(expected_result == exporter.out(), "Wrong json output.");  
}

//=============================================================================
int main() {
  utest_UIBuilder test;
  test.run_tests();
  return 0;
}

#else
NOT_SUPPORTED_MAIN
#endif
