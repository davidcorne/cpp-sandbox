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

  virtual void listen_to(
    const Sender& sender,
    Reason reason,
    int i
  );

private:
};
//=============================================================================
class utest_Sender : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_listening();
  }

private:

  void test_listening();

};

Reason TestSender_message;

//=============================================================================
class TestSender : public Sender {
public:

  TestSender();
  virtual ~TestSender();

  void call_1();
  void call_2();

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
  send_call(TestSender_message);
}

//=============================================================================
void TestSender::call_2() {
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
TestReceiver::TestReceiver(TestSender& test_sender)
  : m_received(false)
{
  listen_to(test_sender, TestSender_message, [this](){callback();});
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
void utest_Sender::test_listening()
{
  print(DGC_CURRENT_FUNCTION);
  TestSender sender;
  TestReceiver receiver(sender);
  sender.call_1();
  test(receiver.received(), "Message received.");
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
  m_callbacks.at(reason)();
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

//=============================================================================
void Receiver::listen_to(
  const Sender& sender,
  Reason reason,
  int i
)
{
}

