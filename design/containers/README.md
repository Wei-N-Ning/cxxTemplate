# Class Template

see stack.cpp for a complete walk through of class template, based on 
the book C++ templates: complete guide

## The concept of "Concept"

read: C++ templates: complete guide L1672

> how do we know which options are required for a template to be able to
> get instantiated? The term concept is often used to denote a set of
> constraints that is repeatedly required in a template library.
> for example C++ standard library relies on such concepts as random access
> iterator and default constructible
> currently (as of C++17) concepts can more or less only be expressed in 
> the documentation.
> this can become a significant problem because failures to follow constraints
> can lead to terrible error messages

how to express the concept constraints in C++17

> since C+11 you can at least check for some basic constraints by using the
> static_assert keyword and some predefined type traits

see stack.cpp for a live example

## Empty Class Optimization

## Curious Recurring Template Pattern (CRTP)

c++ template: complete guide L17299

see: curious_recurring_template.cpp

> by passing the derived class down to its base class via a template parameter
> the base class can customize its own behavior to the derived class without
> requiring the use of virtual functions
> this makes CRTP useful to factor out impl that can only be member functions
> ctor, detor and subscript operators, or are dependent on the derived class's
> identity
