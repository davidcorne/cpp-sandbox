//=============================================================================
//
// 

#include <iostream>
#include <functional>
#include <map>

#include <UnitCpp/Test.h>

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
  
  virtual void send_call(Reason reason, void* data);
  
private:
  friend class Receiver;
  
  virtual void add_receiver(Reason reason, std::function<void(void*)> callback);

  std::map<Reason, std::function<void(void*)> > m_callbacks;
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
    std::function<void(void*)> callback
  );

private:
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
  void* data = 0;
  send_call(TestSender_message_1, data);
}

//=============================================================================
void TestSender::call_2() {
  void* data = 0;
  send_call(TestSender_message_2, data);
}

//=============================================================================
void TestSender::call_3() {
  void* data = 0;
  send_call(TestSender_message_3, data);
}

//=============================================================================
class TestReceiver : public Receiver {
public:

  TestReceiver(TestSender& test_sender);
  virtual ~TestReceiver();

  bool received() const;
  
private:

  void callback(void* data);
  
  bool m_received;
};

//=============================================================================
static bool GLOBAL_CALLBACK_CALLED = false;

//=============================================================================
void global_callback(void*)
{
  GLOBAL_CALLBACK_CALLED = true;
}

//=============================================================================
TestReceiver::TestReceiver(TestSender& test_sender)
  : m_received(false)
{
  void* data = 0;
  listen_to(
    test_sender,
    TestSender_message_1,
    std::bind(&TestReceiver::callback, this, data)
  );
  listen_to(
    test_sender,
    TestSender_message_2,
    [this](void* data){callback(data);}
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
void TestReceiver::callback(void*)
{
  m_received = true;
}

//=============================================================================
TEST(Sender, listening_1)
{
  TestSender sender;
  TestReceiver receiver(sender);
  TEST_FALSE(receiver.received(), "receiver has not received anything.");
  sender.call_1();
  TEST_TRUE(receiver.received(), "Message received.");
}

//=============================================================================
TEST(Sender, listening_2)
{
  TestSender sender;
  TestReceiver receiver(sender);
  TEST_FALSE(receiver.received());
  sender.call_2();
  TEST_TRUE(receiver.received(), "Message received.");
}

//=============================================================================
TEST(Sender, listening_3)
{
  TestSender sender;
  TestReceiver receiver(sender);
  TEST_FALSE(GLOBAL_CALLBACK_CALLED);
  sender.call_3();
  TEST_TRUE(GLOBAL_CALLBACK_CALLED, "global callback called.");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
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
void Sender::send_call(Reason reason, void* data)
{
  if (end(m_callbacks) != m_callbacks.find(reason)) {
    m_callbacks.at(reason)(data);
  }
}

//=============================================================================
void Sender::add_receiver(Reason reason, std::function<void(void*)> callback)
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
  std::function<void(void*)> callback
)
{
  Sender& unconst_sender = const_cast<Sender&>(sender);
  unconst_sender.add_receiver(reason, callback);
}

