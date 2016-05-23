//=============================================================================
class A {
public:
  void g() {}
};

//=============================================================================
class B {
public:
  B(A& a) : m_a(a) {}
  void f() const {
    m_a.g();
  }

  B(const B&) = delete;
  B& operator=(const B&) = delete;
  
private:
  A& m_a;
};

//=============================================================================
int main()
{
  A a;
  B b(a);
  b.f();
  return 0;
}

