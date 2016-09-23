#include <UnitCpp.h>

#include "LoggingAllocator.h"
#include "LoggingAllocator.h"

//=============================================================================
TEST(LoggingAllocator, allocate)
{
  std::stringstream ss;
  LoggingAllocator<int> allocator(&ss);
  int* i = allocator.allocate(sizeof(int));
  TEST_TRUE(i);
}

//=============================================================================
TEST(LoggingAllocator, deallocate)
{
  int* i = new int(5);
  LoggingAllocator<int> allocator;
  allocator.deallocate(i, sizeof(int));
}

//=============================================================================
TEST(LoggingAllocator, log)
{
  std::stringstream ss;
  LoggingAllocator<int> allocator(&ss);
  int* i = allocator.allocate(sizeof(int));
  std::stringstream message;
  message << "Allocated " << sizeof(int) << " bytes.\n";
  std::cout << ss.str();
  TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);

  message.str("");
  message << "Deallocated " << sizeof(int) << " bytes.\n";
  allocator.deallocate(i, sizeof(int));
  std::cout << ss.str();
  TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);
}

//=============================================================================
TEST(LoggingAllocator, settings)
{
  {
    std::stringstream ss;
    LoggingAllocator<int, true, true> allocator(&ss);
    int* i = allocator.allocate(sizeof(int));
    std::stringstream message;
    message << "Allocated " << sizeof(int) << " bytes.\n";
    std::cout << ss.str();
    TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);

    message.str("");
    message << "Deallocated " << sizeof(int) << " bytes.\n";
    allocator.deallocate(i, sizeof(int));
    std::cout << ss.str();
    TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);
  }
  {
    std::stringstream ss;
    LoggingAllocator<int, false, true> allocator(&ss);
    int* i = allocator.allocate(sizeof(int));
    std::stringstream message;
    message << "Allocated " << sizeof(int) << " bytes.\n";
    std::cout << ss.str();
    TEST_EQUAL(ss.str().find(message.str()), std::string::npos);

    message.str("");
    message << "Deallocated " << sizeof(int) << " bytes.\n";
    allocator.deallocate(i, sizeof(int));
    std::cout << ss.str();
    TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);
  }
  {
    std::stringstream ss;
    LoggingAllocator<int, true, false> allocator(&ss);
    int* i = allocator.allocate(sizeof(int));
    std::stringstream message;
    message << "Allocated " << sizeof(int) << " bytes.\n";
    std::cout << ss.str();
    TEST_NOT_EQUAL(ss.str().find(message.str()), std::string::npos);

    message.str("");
    message << "Deallocated " << sizeof(int) << " bytes.\n";
    allocator.deallocate(i, sizeof(int));
    std::cout << ss.str();
    TEST_EQUAL(ss.str().find(message.str()), std::string::npos);
  }
  {
    std::stringstream ss;
    LoggingAllocator<int, false, false> allocator(&ss);
    int* i = allocator.allocate(sizeof(int));
    std::stringstream message;
    message << "Allocated " << sizeof(int) << " bytes.\n";
    std::cout << ss.str();
    TEST_EQUAL(ss.str().find(message.str()), std::string::npos);

    message.str("");
    message << "Deallocated " << sizeof(int) << " bytes.\n";
    allocator.deallocate(i, sizeof(int));
    std::cout << ss.str();
    TEST_EQUAL(ss.str().find(message.str()), std::string::npos);
  }
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
