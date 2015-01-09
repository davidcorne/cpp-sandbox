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

//=============================================================================
// Variable declarations
template <bool TrueResult, bool FalseResult>
constexpr const bool If<true, TrueResult, FalseResult>::result;

template <bool TrueResult, bool FalseResult>
constexpr const bool If<false, TrueResult, FalseResult>::result;


#endif
