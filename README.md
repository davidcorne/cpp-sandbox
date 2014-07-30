# Sandbox #

This repository is a sandbox for trying out ideas in C++ or new features (like C++ 11 stuff).

Each experiment must be one file with extension .cpp. In the main directory it compiles using gcc with argument -std=c++0x if you need the Microsoft compiler put the file in the UnsupportedByCompiler directory

Most files act as a test. These are run automatically on drone.io, [![Build Status](https://drone.io/bitbucket.org/davidcorne/sandbox/status.png)](https://drone.io/bitbucket.org/davidcorne/sandbox/latest)

Here is a short summery of what I was trying to do for some of the files.

## Arrays ##
In this file I was playing around with C style arrays, slightly old and a bit dated to be honest.

## Comparisons ##
This may be a future post here. It defines a templatised base class for comparable class (using the [curiously recurring template pattern](http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)). It means that if you inherit from this class and define one compare function, you get all 6 comparison operators.

## ConstPointer ##
Testing out what you can do with const pointers. With a const Class* const you can only call const methods, with a Class* const you can call anything (this keeps the pointer const not what it points at) and with a Class* you can call anything.


## Constness ##

## CopyReference ##
Trying to copy a reference without using the copy constructor or assignment operator.

## DivideByZero ##
I wondered what compiler errors/warnings you get from dividing by zero?
It turns out (in g++) that it will not give errors at all. It will warn you if you divide by a literal zero or a const zero, but not a variable with value zero.

## ExclusiveOr ##
This was for checking the results of using [xor](http://en.wikipedia.org/wiki/Exclusive_or) on integers. 

## Lambda ##
This was testing the newly added lambda functions, but changed to using [standard template library](http://en.wikipedia.org/wiki/Standard_Template_Library) algorithms.

## MustOverride ##
This was playing around with pure virtual functions with implementations. So you can call them using Base::function() in the derived class.

## Operators ##
Testing calling operator() on pointer. Here is the calling code.

      Foo* f = new Foo();
      (*f)();
      (*f).operator()();
      f->operator()();

      delete f;

A common mistake doing this is to leave off the final brackets so.

      (*f).operator();
      f->operator();

But these will return a function pointer to operator(), they won't call it.

## SelfDeleting ##
Trying to make an executable to delete itself, unsurprisingly this doesn't work.

## StructClass ##
Testing out the differences between structs and classes in C++. I found that apart from private/public as default there is no difference! This includes if you declare class T in a template, you can still use a struct.

## UserDefinedLiterals and UserDefinedLiteralsBinary ##
Trying to use C++ 11 user [defined literals](http://enreference.com/w/cpp/language/user_literal) to be able to use syntax like this:
    Binary two = 10_b;

I was following a good guide from [here](http://akrzemi1.wordpress.com/2012/08/12/user-defined-literals-part-i/).

## VariadicPointerOffset ##

## Windows ##
Unimplemented test for [SetEvent()](http://msdn.microsoft.com/en-gb/library/windows/desktop/ms686211(v=vs.85).aspx) in windows.h.

## hashes ##
Using C preprocessor magic to join together variable names.

## stack\_overflow\_virtual ##
I didn't think the reply to [this question](http://stackoverflow.com/questions/6481260/non-virtual-interface-design-pattern-question-in-c-c) would compile so I tried it out. I realised you can override private virtual functions but not call them.

