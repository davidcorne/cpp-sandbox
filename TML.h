//=============================================================================
// My TemplateMetaprogrammingLibrary

#ifndef TML_H
#define TML_H

#include "Capabilities.h"

#if !CAPABILITY_CONSTEXPR
#error "You need constexpr for this header."
#endif

//=============================================================================
template <bool Condition, bool TrueResult, bool FalseResult>
struct If;

template <bool TrueResult, bool FalseResult>
struct If<true, TrueResult, FalseResult> {
  constexpr static const bool result = TrueResult;
};

template <bool TrueResult, bool FalseResult>
struct If<false, TrueResult, FalseResult> {
  constexpr static const bool result = FalseResult;
};

template <unsigned int LHS, unsigned int RHS>
struct Less {
  constexpr static const bool result = LHS < RHS;
};

//=============================================================================
template <unsigned int In, unsigned int Guess>
struct _SqrtFinder {

  // int sqrt(In, Guess) {
  //   if (Guess * Guess < In) {
  //     return sqrt(Guess + 1);
  //   } else {
  //     return Guess;
  //   }
  //   
  // }
        
  constexpr static const unsigned int result = 
    If<
      Less<Guess * Guess, In>::result,
      _SqrtFinder<In, Guess + 1>::result,
      Guess
    >::result;
};

//=============================================================================
template <unsigned int In>
struct Sqrt {
  constexpr static const unsigned int result = _SqrtFinder<In, 0>::result;
};

//=============================================================================
// Variable declarations
template <bool TrueResult, bool FalseResult>
constexpr const bool If<true, TrueResult, FalseResult>::result;

template <bool TrueResult, bool FalseResult>
constexpr const bool If<false, TrueResult, FalseResult>::result;

template <unsigned int In>
constexpr const unsigned int Sqrt<In>::result;

//=============================================================================
template <unsigned int LHS, unsigned int RHS>
constexpr const bool Less<LHS, RHS>::result;
#endif
