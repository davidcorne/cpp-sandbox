//=============================================================================
//
// A template meta programming list.

#include "Capabilities.h"
#ifdef CAPABILITY_CONSTEXPR
#include <UnitCpp/Test.h>

#define UNUSED_TYPEDEF 1
#include "IgnoreDiagnostics.h"

template <int N>
struct IntValue {
  constexpr static const int value = N;
};

template <int N>
constexpr const int IntValue<N>::value;

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
template <typename tLIST, typename tFUNCTION>
struct ForEach {

  static void execute(tFUNCTION func) {
    func(tLIST::Head::value);
    ForEach<typename tLIST::Tail, tFUNCTION>::execute(func);
  }
  
};

//=============================================================================
template <typename tFUNCTION>
struct ForEach<NullList, tFUNCTION> {

  static void execute(tFUNCTION func) {
  }
  
};

//=============================================================================
template <typename tLIST>
struct Sum {
  constexpr static const int result =
    tLIST::Head::value + Sum<typename tLIST::Tail>::result;
};

//=============================================================================
template <>
struct Sum<NullList> {
  constexpr static const int result = 0;
};

//=============================================================================
template <typename tLIST>
constexpr const int Sum<tLIST>::result;

//=============================================================================
constexpr const int Sum<NullList>::result;

//=============================================================================
TEST(MetaList, construction)
{
  typedef List<IntValue<1>, List<IntValue<2> > > ListOneTwo;
}

//=============================================================================
TEST(MetaList, length)
{
  typedef List<IntValue<1>, List<IntValue<2> > > ListOneTwo;
  TEST_EQUAL(Length<ListOneTwo>::result, 2);
  typedef List<IntValue<1>, List<IntValue<2>, List<IntValue<3> > > > ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
}

//=============================================================================
TEST(MetaList, Nth)
{
  typedef List<IntValue<1>, List<IntValue<2>, List<IntValue<3> > > > ListOneTwoThree;
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
}

//=============================================================================
TEST(MetaList, append)
{
  typedef Append<IntValue<1>, NullList>::result ListOne;
  TEST_EQUAL((Nth<ListOne, 0>::result::value), 1);
  TEST_EQUAL(Length<ListOne>::result, 1);

  typedef Append<IntValue<2>, ListOne>::result ListOneTwo;
  TEST_EQUAL((Nth<ListOne, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwo, 1>::result::value), 2);
  TEST_EQUAL(Length<ListOneTwo>::result, 2);

  typedef Append<IntValue<3>, ListOneTwo>::result ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
  TEST_EQUAL((Nth<ListOneTwoThree, 2>::result::value), 3);
  
}

//=============================================================================
TEST(MetaList, prepend)
{
  typedef List<IntValue<2>, List<IntValue<3> > > ListTwoThree;
  typedef Prepend<IntValue<1>, ListTwoThree>::result ListOneTwoThree;
  TEST_EQUAL(Length<ListOneTwoThree>::result, 3);
  TEST_EQUAL((Nth<ListOneTwoThree, 0>::result::value), 1);
  TEST_EQUAL((Nth<ListOneTwoThree, 1>::result::value), 2);
  TEST_EQUAL((Nth<ListOneTwoThree, 2>::result::value), 3);
}

//=============================================================================
TEST(MetaList, for_each)
{
  typedef List<IntValue<1>, List<IntValue<2>, List<IntValue<3> > > > ListOneTwoThree;
  int total = 0;
  auto sum = [&total](int i){total += i;};
  ForEach<ListOneTwoThree, decltype(sum)>::execute(sum);
  TEST_EQUAL(total, 6);
}

//=============================================================================
TEST(MetaList, sum)
{
  typedef List<IntValue<1>, List<IntValue<2>, List<IntValue<3> > > > ListOneTwoThree;
  TEST_EQUAL(Sum<ListOneTwoThree>::result, 6);
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN(CAPABILITY_CONSTEXPR)
#endif
