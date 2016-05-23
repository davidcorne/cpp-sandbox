//=============================================================================
//
//D Inspired by
// http://gameprogrammingpatterns.com/event-queue.html

#include "RingBuffer.h"

#include "Capabilities.h"
#ifdef CAPABILITY_INITIALISER_LISTS
#include <iostream>
#include <string>

#include <UnitCpp.h>

//=============================================================================
struct Request {
  int Num;
  std::string Descriptiton;
};

typedef Ring<Request> RequestRing;

//=============================================================================
TEST(RingBuffer, add)
{
  RequestRing ring;
  Request request = {0, "Hey"};
  ring.add(request);
  request = ring.update();
  TEST_EQUAL(request.Num, 0, "Correct Num.");
  TEST_EQUAL(request.Descriptiton, "Hey", "Correct Descriptiton.");
}

//=============================================================================
TEST(RingBuffer, max_size)
{
  TEST_EQUAL(RequestRing().max_size(), 5, "Wrong max size");
}

//=============================================================================
TEST(RingBuffer, count)
{
  RequestRing ring;
  TEST_EQUAL(ring.size(), 0, "Wrong size");

  Request request = {0, "Hey"};
  ring.add(request);
  TEST_EQUAL(ring.size(), 1, "Wrong size");

  request = {1, "Hey"};
  ring.add(request);
  TEST_EQUAL(ring.size(), 2, "Wrong size");

  request = {2, "Hey"};
  ring.add(request);
  TEST_EQUAL(ring.size(), 3, "Wrong size");

  request = {3, "Hey"};
  ring.add(request);
  TEST_EQUAL(ring.size(), 4, "Wrong size");

  ring.update();
  ring.update();
  TEST_EQUAL(ring.size(), 2, "Wrong size");

  ring.add(request);
  ring.add(request);
  TEST_EQUAL(ring.size(), 4, "Wrong size");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_INITIALISER_LISTS)
#endif

