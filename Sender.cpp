//=============================================================================
//
// 

#include <iostream>
#include <functional>
#include <map>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class Reason {
public:

  Reason();
  ~Reason();

  Reason(const Reason& reason);
  Reason& operator=(const Reason& reason);
  
  bool operator<(const Reason& reason) const;
  
private:
  static int s_next_id;
  // Make each reason instance unique.

  int m_id;
};

class Receiver;

//=============================================================================
class Sender {
public:

  Sender();
  virtual ~Sender() = 0;

protected:
  
  virtual void send_call(Reason reason);
  
private:
  friend class Receiver;
  
  virtual void add_receiver(Reason reason, function<void(void)> callback);

  map<Reason, function<void(void)> > m_callbacks;
  friend class utest_Sender;
};

//=============================================================================
class Receiver {

public:

  Receiver();
  virtual ~Receiver() = 0;

  virtual void listen_to(
    const Sender& sender,
    Reason reason,
    function<void(void)> callback
  );

private:
};

//=============================================================================
class utest_Sender : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_listening_1();
    test_listening_2();
    test_listening_3();
  }

private:

  void test_listening_1();
  void test_listening_2();
  void test_listening_3();

};

Reason TestSender_message_1;
Reason TestSender_message_2;
Reason TestSender_message_3;

//=============================================================================
class TestSender : public Sender {
public:

  TestSender();
  virtual ~TestSender();

  void call_1();
  void call_2();
  void call_3();

private:
};

//=============================================================================
TestSender::TestSender()
{
}

//=============================================================================
TestSender::~TestSender()
{
}

//=============================================================================
void TestSender::call_1() {
  send_call(TestSender_message_1);
}

//=============================================================================
void TestSender::call_2() {
  send_call(TestSender_message_2);
}

//=============================================================================
void TestSender::call_3() {
  send_call(TestSender_message_3);
}

//=============================================================================
class TestReceiver : public Receiver {
public:

  TestReceiver(TestSender& test_sender);
  virtual ~TestReceiver();

  bool received() const;
  
private:

  void callback();
  
  bool m_received;
};

//=============================================================================
static bool GLOBAL_CALLBACK_CALLED = false;

//=============================================================================
void global_callback()
{
  GLOBAL_CALLBACK_CALLED = true;
}

//=============================================================================
TestReceiver::TestReceiver(TestSender& test_sender)
  : m_received(false)
{
  listen_to(
    test_sender,
    TestSender_message_1,
    bind(&TestReceiver::callback, this)
  );
  listen_to(
    test_sender,
    TestSender_message_2,
    [this](){callback();}
  );
  listen_to(
    test_sender,
    TestSender_message_3,
    global_callback
  );
}

//=============================================================================
TestReceiver::~TestReceiver()
{
}

//=============================================================================
bool TestReceiver::received() const
{
  return m_received;
}

//=============================================================================
void TestReceiver::callback()
{
  m_received = true;
}

//=============================================================================
void utest_Sender::test_listening_1()
{
  print(DGC_CURRENT_FUNCTION);
  TestSender sender;
  TestReceiver receiver(sender);
  assert(!receiver.received());
  sender.call_1();
  test(receiver.received(), "Message received.");
}

//=============================================================================
void utest_Sender::test_listening_2()
{
  print(DGC_CURRENT_FUNCTION);
  TestSender sender;
  TestReceiver receiver(sender);
  assert(!receiver.received());
  sender.call_2();
  test(receiver.received(), "Message received.");
}

//=============================================================================
void utest_Sender::test_listening_3()
{
  print(DGC_CURRENT_FUNCTION);
  TestSender sender;
  TestReceiver receiver(sender);
  assert(!GLOBAL_CALLBACK_CALLED);
  sender.call_3();
  test(GLOBAL_CALLBACK_CALLED, "global callback called.");
}

//=============================================================================
int main() {
  utest_Sender test;
  test.run_tests();
  return 0;
}

int Reason::s_next_id(0);
// Static initialisation.

//=============================================================================
Reason::Reason()
  : m_id(s_next_id)
{
  ++s_next_id;
}

//=============================================================================
Reason::Reason(const Reason& reason)
  : m_id(reason.m_id)
{
}

//=============================================================================
Reason& Reason::operator=(const Reason& reason)
{
  m_id = reason.m_id;
  return *this;
}

//=============================================================================
Reason::~Reason()
{
}

//=============================================================================
bool Reason::operator<(const Reason& reason) const
{
  return m_id < reason.m_id;
}

//=============================================================================
Sender::Sender()
{
}

//=============================================================================
Sender::~Sender()
{
}

//=============================================================================
void Sender::send_call(Reason reason)
{
  if (end(m_callbacks) != m_callbacks.find(reason)) {
    m_callbacks.at(reason)();
  }
}

//=============================================================================
void Sender::add_receiver(Reason reason, function<void(void)> callback)
{
  m_callbacks[reason] = callback;
}

//=============================================================================
Receiver::Receiver()
{
}

//=============================================================================
Receiver::~Receiver()
{
}

//=============================================================================
void Receiver::listen_to(
  const Sender& sender,
  Reason reason,
  function<void(void)> callback
)
{
  Sender& unconst_sender = const_cast<Sender&>(sender);
  unconst_sender.add_receiver(reason, callback);
}

