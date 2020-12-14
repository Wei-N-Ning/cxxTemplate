# Template Parameter

recall Haskell's type parameter and type-driven development

## Pretty-print function sig

introduced in modern c++ programming cookbook L3280

> by adding a `std::cout << __PRETTY_FUNCTION__ << std::endl;` at the beginning
> of the functions we wrote, we get the following:

if I need to see **the fully instantiated form of a function template**, stick this
magic print statement inside the template

## Non-type parameters

C++ templates: complete guide L/2211

> template params do not have to be types; they can also be ordinary values
> as with templates using type params, you define code for which a certain
> detail remains open util the code is used. However the detail that is open
> is a value instead of a type

see fixed_size_stack.cpp for complete walk through.

## Variadic Templates

C++ templates: complete guide L2530

see variadic.cpp

### Variadic function call that works with ANY function 

i.e. implementing f(xs) ... which the standard does not provide

see: variadic_istream_tuple.cpp
