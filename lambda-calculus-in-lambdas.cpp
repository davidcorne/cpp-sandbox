//=============================================================================
// This is an attempt to encode the lambda calculus using C++14 lambdas.

#include <iostream>

#include <UnitCpp/Test.h>

#include "Capabilities.h"
#ifdef GENERIC_LAMBDAS

#define UNUSED_VARIABLE 1
#include "IgnoreDiagnostics.h"
#include <stdexcept>

// A function-level Pressburger encoding of natural numbers.

// A lambda for 0:
auto lit = [](auto x)
{
  return [x](){return x;};
};

auto zero = [](){return 0;};

// 1 == succ(zero)
// 2 == succ(succ(zero))
// ...
auto succ = [](auto n){return lit(n() + 1);};


// The syntax contains five expression types: lambda terms for
// anonymous functions, function applications, variable references,
// conditionals and literals.

// Core syntax:
auto lambda = [](auto name, auto body) {};

auto application = [](auto func, auto arg) {};

auto ref = [](auto name) {};

// Sugar:

auto if_func = [](auto condition, auto func_a, decltype(func_a) func_b)
{
  return lit(condition() ? func_a : func_b);
};

// Environments are functions that map (variable) names to values.
// Environments are paired with expressions to give meanings to free
// variables.

// EmptyEnv is the empty environment.

auto empty_env = [](auto l){
  throw std::runtime_error("Empty env.");
  return lit(-1);
};

// Bindings<Name,Value,Env> is a type than encodes the environment Env
// extended with a binding for Name => Value.
auto binding = [](auto name, auto value, auto env) {
  typedef std::function<decltype(name)()> Val;
  auto new_env = [=](auto new_name)->Val {
    if (new_name == name) {
      return value;
    }
    return env(new_name);
  };
  return new_env;  
};

// EnvLookup<Name,Env> :: result looks up the value of Name in Env.
auto env_lookup = [](auto name, auto env){return env(name);};

// Values:
auto closure = [](auto lambda, auto env){};

auto true_func = [](){return lit(true);};
auto false_func = [](){return lit(false);};

// We use Eval & Apply-style interpreter [SICP].

// Eval<Exp,Env> :: result is the value of expression Exp in
// environment Env.
auto eval = [](auto exp, auto env){}; // something like exp(env)

auto apply = [](auto procedure, auto value){};



//=============================================================================
TEST(LambdaCalculus, test)
{
  auto environment = binding(2, succ(zero), binding(3, zero, empty_env));

  // Testing [2 => 1, 3 => 0](3), [2 => 1, 3 => 0](2)

  TEST_EQUAL(env_lookup(3, environment)(), 0);
  TEST_EQUAL(env_lookup(2, environment)(), 1);


  // <nnn> // Testing ((lambda (x) x) 2):
  // <nnn> enum { X } ;
  
  // <nnn> int x = eval(application(lambda(X, ref(X)), lit(succ(succ(0)))), empty_env);
  // <nnn> TEST_EQUAL(x, 2);


  // <nnn> // Testing (if #f 0 1):
  // <nnn> int y = eval(if_func(lit(false_func), lit(zero), lit(succ(zero))), empty_env);
  // <nnn> TEST_EQUAL(y, 1);
}


//=============================================================================
int main (int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
#else
UNSUPPORTED_FEATURE_MAIN;
#endif
