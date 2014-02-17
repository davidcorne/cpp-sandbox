//=============================================================================
//
// Motivated by this:
// http://www.objectmentor.com/resources/articles/acv.pdf

#include "UnitTest.h"
#include "compiler_guards.h"

#if CPP_ELEVEN_SUPPORTED

//=============================================================================
// Degenerate class, only used for passing around. Anyone who wants to use
// methods will need to cast to a derived class.
class odiParameters {
public:

  virtual ~odiParameters() = 0;
};

//=============================================================================
class odiAccomParamaters : public odiParameters {
public:

  virtual void set_heel_back_eval_height(double d) = 0;

  virtual double heel_back_eval_height() const = 0;
};

//=============================================================================
class odiFuncParamaters : public odiParameters {
public:

  virtual void set_orthotic_thickness(double d) = 0;

  virtual double orthotic_thickness() const = 0;
};

//=============================================================================
// Concept of this class is you may want to store loose and tight parameters
// differently, they would have the same interface
class ordLooseAccomParamaters : public odiAccomParamaters {
public:

  ordLooseAccomParamaters();
    
  virtual void set_heel_back_eval_height(double d) override;

  virtual double heel_back_eval_height() const override;
  
private:

  double m_heel_back_evaluation_height;
  
};

//=============================================================================
class ordFuncParamaters : public odiFuncParamaters {
public:

  ordFuncParamaters();
    
  virtual void set_orthotic_thickness(double d);

  virtual double orthotic_thickness() const;
  
private:

  double m_thickness;
  
};

//=============================================================================
class odiOrthotic {
public:

  virtual odiParameters* get_pars() = 0;

  virtual ~odiOrthotic() = 0;

};

//=============================================================================
class ordLooseAccomOrthotic : public odiOrthotic {
public:

  ordLooseAccomOrthotic();
  
  virtual odiParameters* get_pars() override;

  virtual ~ordLooseAccomOrthotic();
  
private:
  ordLooseAccomParamaters* m_pars;
};

//=============================================================================
class ordFuncOrthotic : public odiOrthotic {
public:

  ordFuncOrthotic();
  
  virtual odiParameters* get_pars() override;

  virtual ~ordFuncOrthotic();
  
private:
  ordFuncParamaters* m_pars;
};

//=============================================================================
class ortParamaterTranslator {
public:

  ortParamaterTranslator(odiParameters& parameters);
  
  const odiAccomParamaters* accom_parameters() const;
  // Postcondition: odiAccomParamaters* is not null.
  
  odiAccomParamaters* accom_parameters_editable();
  // Postcondition: odiAccomParamaters* is not null.

  const odiFuncParamaters* func_parameters() const;
  // Postcondition: odiFuncParamaters* is not null.
  
  odiFuncParamaters* func_parameters_editable();
  // Postcondition: odiFuncParamaters* is not null.

private:

  odiParameters& m_parameters;
  
};

//=============================================================================
class ortParameterDataModel {
public:

  ortParameterDataModel(odiOrthotic& orthotic);
  
  void set_heel_back_eval_height(double d);

  double heel_back_eval_height() const;

  void set_orthotic_thickness(double d);
  
  double orthotic_thickness() const;
  
private:
  ortParamaterTranslator m_translator;
};

//=============================================================================
// Basically what an IC class would do
class utest_Orthotic : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_accom();
    test_func();
  }

private:

  void test_accom();
  void test_func();

};

//=============================================================================
void utest_Orthotic::test_accom()
{
  print(DGC_CURRENT_FUNCTION);
  odiOrthotic* orthotic = new ordLooseAccomOrthotic();
  ortParameterDataModel dm(*orthotic);
  dm.set_heel_back_eval_height(10.0);
  test(
    dm.heel_back_eval_height() == 10.0,
    "Correctly set/got heel_back_eval_height"
  );
  delete orthotic;
}

//=============================================================================
void utest_Orthotic::test_func()
{
  print(DGC_CURRENT_FUNCTION);
  odiOrthotic* orthotic = new ordFuncOrthotic();
  ortParameterDataModel dm(*orthotic);
  dm.set_orthotic_thickness(4.0);
  test(
    dm.orthotic_thickness() == 4.0,
    "Correctly set/got orthotic thickness"
  );
  delete orthotic;
}

//=============================================================================
int main() {
  utest_Orthotic test;
  test.run_tests();
  return 0;
}

//=============================================================================
// Virtual Classes
//=============================================================================

//=============================================================================
odiParameters::~odiParameters()
{
}

//=============================================================================
odiOrthotic::~odiOrthotic()
{
}

//=============================================================================
// ordLooseAccomParamaters
//=============================================================================

//=============================================================================
ordLooseAccomParamaters::ordLooseAccomParamaters()
: m_heel_back_evaluation_height(0)
{
}

//=============================================================================
void ordLooseAccomParamaters::set_heel_back_eval_height(double d)
{
  m_heel_back_evaluation_height = d;
}

//=============================================================================
double ordLooseAccomParamaters::heel_back_eval_height() const
{
  return m_heel_back_evaluation_height;
}

//=============================================================================
// ordFuncParamaters
//=============================================================================

//=============================================================================
ordFuncParamaters::ordFuncParamaters()
: m_thickness(0)
{
}

//=============================================================================
void ordFuncParamaters::set_orthotic_thickness(double d)
{
  m_thickness = d;
}

//=============================================================================
double ordFuncParamaters::orthotic_thickness() const
{
  return m_thickness;
}

//=============================================================================
// ordLooseAccomOrthotic
//=============================================================================

//=============================================================================
ordLooseAccomOrthotic::ordLooseAccomOrthotic()
  : m_pars(0)
{
  m_pars = new ordLooseAccomParamaters;
}
  
//=============================================================================
odiParameters* ordLooseAccomOrthotic::get_pars()
{
  assert(m_pars);
  return m_pars;
}

//=============================================================================
ordLooseAccomOrthotic::~ordLooseAccomOrthotic()
{
  delete m_pars;
}

//=============================================================================
// ordFuncOrthotic
//=============================================================================

//=============================================================================
ordFuncOrthotic::ordFuncOrthotic()
  : m_pars(0)
{
  m_pars = new ordFuncParamaters;
}
  
//=============================================================================
odiParameters* ordFuncOrthotic::get_pars()
{
  assert(m_pars);
  return m_pars;
}

//=============================================================================
ordFuncOrthotic::~ordFuncOrthotic()
{
  delete m_pars;
}

//=============================================================================
// odiParamaterTranslator
//=============================================================================

//=============================================================================
ortParamaterTranslator::ortParamaterTranslator(odiParameters& parameters)
  : m_parameters(parameters)
{
}

//=============================================================================
const odiAccomParamaters* ortParamaterTranslator::accom_parameters() const
// Postcondition: odiAccomParamaters* is not null.
{
  odiAccomParamaters* pars =
    const_cast<ortParamaterTranslator*>(this)->accom_parameters_editable();
  return const_cast<const odiAccomParamaters* >(pars);
}
  
//=============================================================================
odiAccomParamaters* ortParamaterTranslator::accom_parameters_editable()
// Postcondition: odiAccomParamaters* is not null.
{
  odiAccomParamaters* accom_pars =
    dynamic_cast<odiAccomParamaters*>(&m_parameters);
  assert(accom_pars);
  return accom_pars;
}

//=============================================================================
const odiFuncParamaters* ortParamaterTranslator::func_parameters() const
// Postcondition: odiFuncParamaters* is not null.
{
  odiFuncParamaters* pars =
    const_cast<ortParamaterTranslator*>(this)->func_parameters_editable();
  return const_cast<const odiFuncParamaters* >(pars);
}
  
//=============================================================================
odiFuncParamaters* ortParamaterTranslator::func_parameters_editable()
// Postcondition: odiFuncParamaters* is not null.
{
  odiFuncParamaters* func_pars =
    dynamic_cast<odiFuncParamaters*>(&m_parameters);
  assert(func_pars);
  return func_pars;
}

//=============================================================================
// ortParameterDataModel
//=============================================================================

//=============================================================================
ortParameterDataModel::ortParameterDataModel(odiOrthotic& orthotic)
  : m_translator(*(orthotic.get_pars()))
{
}

//=============================================================================
void ortParameterDataModel::set_heel_back_eval_height(double d)
{
  odiAccomParamaters* accom_pars =
    m_translator.accom_parameters_editable();
  accom_pars->set_heel_back_eval_height(d);
}

//=============================================================================
double ortParameterDataModel::heel_back_eval_height() const
{
  const odiAccomParamaters* accom_pars = m_translator.accom_parameters();
  return accom_pars->heel_back_eval_height();
}
  
//=============================================================================
void ortParameterDataModel::set_orthotic_thickness(double d)
{
  odiFuncParamaters* func_pars =
    m_translator.func_parameters_editable();
  func_pars->set_orthotic_thickness(d);
}

//=============================================================================
double ortParameterDataModel::orthotic_thickness() const
{
  const odiFuncParamaters* func_pars = m_translator.func_parameters();
  return func_pars->orthotic_thickness();
}
  
#else
NOT_SUPPORTED_MAIN
#endif
