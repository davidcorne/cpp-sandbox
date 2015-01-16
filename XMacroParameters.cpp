//=============================================================================
//

#include <UnitCpp.h>

#define UNUSED_PRIVATE_FIELD
#include "IgnoreDiagnostics.h"
#undef UNUSED_PRIVATE_FIELD

//----- Header type section

// these are the shared parameters for all vehicles.
#define VEHICLE_PARAMETERS                              \
  X(NumberOfWheels, int, number_of_wheels, Vehicle, 0)  \
  X(Make, std::string, make, Vehicle, "Unknown")        \
  

#define BIKE_PARAMETERS                                     \
  X(SidecarAttached, bool, side_car_attached, Bike, false)  \
  VEHICLE_PARAMETERS                                        \


#define CAR_PARAMETERS                              \
  X(NumberOfDoors, int, number_of_doors, Car, 3)    \
  VEHICLE_PARAMETERS                                \
  

//=============================================================================
class CarParameters {
public:

  CarParameters();
  ~CarParameters();
  
#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, ...) \
  PARAMETER_TYPE PARAMETER_FUNCTION_NAME() const;                       \
  void set_##PARAMETER_FUNCTION_NAME(PARAMETER_TYPE value);             \
  
  CAR_PARAMETERS
#undef X

  private:

  friend bool operator==(const CarParameters& a, const CarParameters& b);

#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, ...) \
  PARAMETER_TYPE m_##PARAMETER_FUNCTION_NAME;                           \
  
  CAR_PARAMETERS
#undef X
  // m_padding is to stop the trailing comma in the initialisation list.
  void* m_padding;
};

bool operator==(const CarParameters& a, const CarParameters& b);
bool operator!=(const CarParameters& a, const CarParameters& b);

std::ostream& operator<<(std::ostream& os, const CarParameters& car_parameters);
  
//---- Tests

//=============================================================================
TEST(XMacroParameters, CarParametersValues)
{
  CarParameters parameters;
  TEST_EQUAL(parameters.number_of_doors(), 3);
  parameters.set_number_of_doors(5);
  TEST_EQUAL(parameters.number_of_doors(), 5);
}

//=============================================================================
TEST(XMacroParameters, CarParametersEquality)
{
  CarParameters a;
  CarParameters b;
  TEST_EQUAL(a, b);
  a.set_number_of_wheels(6);
  TEST_FALSE(a == b);
}

//=============================================================================
TEST(XMacroParameters, CarParametersInequality)
{
  CarParameters a;
  CarParameters b;
  TEST_FALSE(a != b);
  a.set_number_of_wheels(6);
  TEST_NOT_EQUAL(a, b);
}

//=============================================================================
TEST(XMacroParameters, CarParametersOutput)
{
  CarParameters a;
  std::stringstream ss;
  ss << a;
  TEST_EQUAL(
    ss.str(),
    "<CarParameters>\n"
    "  <NumberOfDoors>3</NumberOfDoors>\n"
    "  <NumberOfWheels>0</NumberOfWheels>\n"
    "  <Make>Unknown</Make>\n"
    "</CarParameters>\n"
  );

  ss.str("");
  a.set_number_of_wheels(4);
  ss << a;
  TEST_EQUAL(
    ss.str(),
    "<CarParameters>\n"
    "  <NumberOfDoors>3</NumberOfDoors>\n"
    "  <NumberOfWheels>4</NumberOfWheels>\n"
    "  <Make>Unknown</Make>\n"
    "</CarParameters>\n"
  );
    
}

//---- Main

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//---- Source

CarParameters::CarParameters()
  :
#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, PARAMETER_SET, PARAMETER_DEFAULT, ...) \
  m_##PARAMETER_FUNCTION_NAME(PARAMETER_DEFAULT),                       \
  
  CAR_PARAMETERS
#undef X
  m_padding(nullptr)
{
}

CarParameters::~CarParameters()
{
}

#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, ...) \
  PARAMETER_TYPE CarParameters::PARAMETER_FUNCTION_NAME() const         \
  {                                                                     \
    return m_##PARAMETER_FUNCTION_NAME;                                 \
  }                                                                     \
                                                                        \
  void CarParameters::set_##PARAMETER_FUNCTION_NAME(PARAMETER_TYPE value) \
  {                                                                     \
    m_##PARAMETER_FUNCTION_NAME = value;                                \
  }                                                                     \
  
CAR_PARAMETERS
#undef X

//=============================================================================
bool operator==(const CarParameters& a, const CarParameters& b)
{
#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, ...) \
  if (a.PARAMETER_FUNCTION_NAME() != b.PARAMETER_FUNCTION_NAME()) {     \
    return false;                                                       \
  }                                                                     
  
  CAR_PARAMETERS
#undef X
  return true;  
}

//=============================================================================
bool operator!=(const CarParameters& a, const CarParameters& b)
{
  return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const CarParameters& car_parameters)
{
  os << "<CarParameters>\n";
#define X(PARAMETER_NAME, PARAMETER_TYPE, PARAMETER_FUNCTION_NAME, ...) \
  os                                                                    \
    << "  <" << #PARAMETER_NAME << ">"                                  \
    << car_parameters.PARAMETER_FUNCTION_NAME()                         \
    << "</" << #PARAMETER_NAME << ">\n";                                \

  CAR_PARAMETERS
  os << "</CarParameters>\n";
  return os;
}
