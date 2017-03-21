#include "RingAllocator.h"
#include "RingAllocator.h"
#include "LoggingAllocator.h"

#include <UnitCpp.h>

#include <functional>

//=============================================================================
TEST(RingAllocator, vector)
{
  RingAllocator<int, 256> allocator;
  
  std::vector<int, decltype(allocator)> vector_1(allocator);
  std::vector<int, decltype(allocator)> vector_2(allocator);
  std::vector<int, decltype(allocator)> vector_3(allocator);
  for (int i = 0; i < 15; ++i) {
    vector_1.insert(end(vector_1), {i, i, i});
    vector_2.insert(end(vector_2), {i, i});
    vector_3.insert(end(vector_3), i);
  }
  
}

//=============================================================================
TEST(RingAllocator, leak_catching)
{
  // <nnn> std::function<void()> leak = [](){
  // <nnn>   {
  // <nnn>     RingAllocator<int> allocator;
  // <nnn>     allocator.allocate(1);
  // <nnn>   }
  // <nnn> };
  // <nnn> TEST_THROWS(leak, RingAllocator<int>::MemoryLeak);
}

//=============================================================================
TEST(RingAllocator, usage)
{
  RingAllocator<int> allocator;
  int* ptr_1 = allocator.allocate(20);
  TEST_EQUAL(allocator.usage().count(), 20u);
  
  int* ptr_2 = allocator.allocate(15);
  TEST_EQUAL(allocator.usage().count(), 35u);

  allocator.deallocate(ptr_1, 20);
  TEST_EQUAL(allocator.usage().count(), 15u);

  int* ptr_3 = allocator.allocate(18);
  TEST_EQUAL(allocator.usage().count(), 33u);

  int* ptr_4 = allocator.allocate(2);
  TEST_EQUAL(allocator.usage().count(), 35u);

  stop_printing();
  // The first 35 bits should be used, test that
  for (std::size_t i = 0; i < 35; ++i) {
    TEST_TRUE(allocator.usage().test(i));
  }

  // The last bits should be not used, test that
  for (std::size_t i = 35; i < allocator.usage().size(); ++i) {
    TEST_FALSE(allocator.usage().test(i));
  }
  restart_printing();

  allocator.deallocate(ptr_3, 18);
  TEST_EQUAL(allocator.usage().count(), 17u);

  allocator.deallocate(ptr_4, 2);
  TEST_EQUAL(allocator.usage().count(), 15u);

  allocator.deallocate(ptr_2, 15);
  TEST_EQUAL(allocator.usage().count(), 0u);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
 
