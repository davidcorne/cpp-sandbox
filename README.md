# Sandbox #

This repository is a sandbox for trying out ideas in C++ or new features (like C++ 11 stuff).

Each experiment must be one file with extension .cpp. In the main directory it compiles using gcc with argument -std=c++0x if you need the Microsoft compiler put the file in the UnsupportedByCompiler directory

Here is a short summery of what I wasy trying to do with each file

## Arrays ##
In this file I was playing around with C style arrays, slightly old and a bit dated to be honest.

## Comparisons ##
This may be a future post here. It defines a templatised base class for comparable class (using the <a href="http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern" target="_blank">curiously recurring template pattern</a> . It means that if you inherit from this class and define one compare function, you get all 6 comparison operators.

## ConstPointer ##
Testing out what you can do with const pointers. With a const Class* const you can only call const methods, with a Class* const you can call anything (this keeps the pointer const not what it points at) and with a Class* you can call anything.


## Constness ##
Found an unusual bug and tested it here. If you have a reference (or a pointer) as a member of your class, in a const function you can call non-const functions on the member. This is because it doesn't change the reference (or pointer) which the class keeps, what it does is change is the object it references.

## CopyReference ##
Trying to copy a reference without using the copy constructor or assignment operator.

## DivideByZero ##
I wondered what compiler errors/warnings you get from dividing by zero?
It turns out (in g++) that it will not give errors at all. It will warn you if you divide by a literal zero or a const zero, but not a variable with value zero.

## ExclusiveOr ##
This was for checking the results of using <a href="http://en.wikipedia.org/wiki/Exclusive_or" target="_blank">xor</a> on integers. 

## Lambda ##
This was testing the newly added lambda functions, but changed to using <a href="http://en.wikipedia.org/wiki/Standard_Template_Library" target="_blank">standard template library</a> algorithms.

## MustOverride ##
This was playing around with pure virtual functions with implementations. So you can call them using Base::function() in the derived class.

## Mutable ##
Testing using a mutable member for data caching. This was the basis for the blog post <a href="http://davidcorne.com/2012/10/26/mutable-and-data-caching/" target="_blank">mutable and data caching</a>.

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

## Polygons ##
Archetypal polygon example for inheritance. A base polygon, a derived rectangle and triangle. Not great as you use a width and height for the polygon but not all polygons have it. Also I prepended all the classes with the letter C and allocated the instances as pointers to the base class.

## SelfDeleting ##
Trying to make an executable to delete itself, unsurprisingly this doesn't work.

## SpareMemory ##
Something picked up from a <a href="http://www.gamasutra.com/view/feature/132500/dirty_coding_tricks.php?" target="_blank">dirty programming trick</a> called the programming antihero (if you haven't read that article I can't recommend it enough!). In this there was a game programmer who reserved 2Mb of memory to lose later when memory was tight. I was testing to see how this worked by reserving some memory and checking memory usage. It is had to see the exact memory usage from this sort of thing due to differences in types of memory (i.e. private bytes/working set...) but it certainly took some memory.

## StructClass ##
Testing out the differences between structs and classes in C++. I found that apart from private/public as default there is no difference! This includes if you declare class T in a template, you can still use a struct.

## UserDefinedLiterals and UserDefinedLiteralsBinary ##
Trying to use C++ 11 user <a href="http://enreference.com/w/cpp/language/user_literal" target="_blank">defined literals</a> to be able to use syntax like this:
    Binary two = 10_b;

I was following a good guide from <a href="http://akrzemi1.wordpress.com/2012/08/12/user-defined-literals-part-i/" target="_blank">here</a>.

## VariadicPointerOffset ##
Quite a complicated file. I was trying to use variadic templates to access private methods of a class. Hopefully not of any practical use (it breaks encapsulation and is extremely fragile) but an interesting idea to try, 

## Windows ##
Unimplemented test for <a href="http://msdn.microsoft.com/en-gb/library/windows/desktop/ms686211(v=vs.85).aspx" target="_blank">SetEvent()</a> in windows.h.

## get\_env ##
Made to test getenv from cstdlib for getting environmental variables.

## hashes ##
Using C preprocessor magic to join together variable names.

## number\_of\_coins ##
Given an amount in cents (American currency as it was taken from an answer on stackoverflow) find the number of ways you can make it from quarters, dimes, nickles and pennies. This was taken from <a href="http://stackoverflow.com/a/1107115/1548429" target="_blank">this answer</a>.

## stack\_overflow\_virtual ##
I didn't think the reply to <a href="http://stackoverflow.com/questions/6481260/non-virtual-interface-design-pattern-question-in-c-c" target="_blank">this question</a> would compile so I tried it out. I realised you can override private virtual functions but not call them.

## upper ##
My thoughts about the answer to <a href="http://stackoverflow.com/questions/1096341/function-pointers-casting-in-c" target="_blank">this stackoverflow question</a> being wrong, and my idea for a better way.
