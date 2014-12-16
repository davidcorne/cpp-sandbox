//=============================================================================
//
// A template meta programming list.

#include "Capabilities.h"
#if CAPABILITY_CONSTEXPR
#include <UnitCpp/Test.h>

#define UNUSED_TYPEDEF 1
#include "IgnoreDiagnostics.h"

template <int N>
struct Value {
  constexpr static const int value = N;
};

template <int N>
constexpr const int Value<N>::value;

//=============================================================================
struct NullList {
  typedef NullList Head;
  typedef NullList Tail;
};

//=============================================================================
template <typename tHEAD, typename tTAIL=NullList>
struct List {
  typedef tHEAD Head;
  typedef tTAIL Tail;
};

//=============================================================================
template <typename tLIST>
struct Length {
  constexpr static const int result = 1 + Length<typename tLIST::Tail>::result;
};

//=============================================================================
template <>
struct Length<NullList> {
  constexpr static const int result = 0;
};

template <typename tLIST>
constexpr const int Length<tLIST>::result;

constexpr const int Length<NullList>::result;

//=============================================================================
template <typename tLIST, int N>
struct Nth {
  typedef typename Nth<typename tLIST::Tail, N - 1>::result result;
};

//=============================================================================
template <typename tLIST>
struct Nth<tLIST, 0> {
  typedef typename tLIST::Head result;
};

//=============================================================================
template <typename tVALUE, typename tLIST>
struct Append {
private:
  typedef typename Append<tVALUE, typename tLIST::Tail>::result Next;
public:
  typedef List<typename tLIST::Head, Next> result;
};
          
//=============================================================================
template <typename tVALUE>
struct Append<tVALUE, NullList> {
  typedef List<tVALUE, NullList> result;
};
          
//=============================================================================
template <typename tVALUE, typename tLIST>
struct Prepend {
  typedef List<tVALUE, tLIST> result;
};

//=============================================================================
TEST(MetaList, construction)
{
  typedef List<Value<1>, List<Value<2> > > ListOneTwo;
}

//=============================================================================
TEST(MetaList, length)
{
  typedef List<Value<1>, List<Value<2> > > ListOneTwo;
  TEST_EQUAL(Length<ListOneTwo>::result, 2);
  typedef List<Value<1>, List<Value<2>, List<Value<3> > > > ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
}

//=============================================================================
TEST(MetaList, Nth)
{
  typedef List<Value<1>, List<Value<2>, List<Value<3> > > > ListOneTwoThree;
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
}

//=============================================================================
TEST(MetaList, append)
{
  typedef Append<Value<1>, NullList>::result ListOne;
  TEST_EQUAL((Nth<ListOne, 0>::result::value), 1);
  TEST_EQUAL(Length<ListOne>::result, 1);

  typedef Append<Value<2>, ListOne>::result ListOneTwo;
  TEST_EQUAL((Nth<ListOne, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwo, 1>::result::value), 2);
  TEST_EQUAL(Length<ListOneTwo>::result, 2);

  typedef Append<Value<3>, ListOneTwo>::result ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
  TEST_EQUAL((Nth<ListOneTwoThree, 2>::result::value), 3);
  
}

//=============================================================================
TEST(MetaList, prepend)
{
  typedef List<Value<2>, List<Value<3> > > ListTwoThree;
  typedef Prepend<Value<1>, ListTwoThree>::result ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
  TEST_EQUAL((Nth<ListOneTwoThree, 2>::result::value), 3);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
